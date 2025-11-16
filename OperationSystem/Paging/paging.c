#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define PAGE_SIZE 256       // 每页大小
#define PAGE_COUNT 256      // 总页数
#define FILE_NAME "BACKING_STORE.bin"

// ===== TLB实现 =====
#define TLB_SIZE 16

typedef struct {
    int page_number;
    int frame_number;
    int valid;
} TLBEntry;

TLBEntry tlb[TLB_SIZE];
int tlb_next_replace = 0; // FIFO替换指针
int tlb_access_count = 0;
int tlb_hit_count = 0;

void init_tlb() {
    for (int i = 0; i < TLB_SIZE; i++) {
        tlb[i].valid = 0;
    }
}

int tlb_lookup(int page_number, int* frame_number) {
    tlb_access_count++;
    for (int i = 0; i < TLB_SIZE; i++) {
        if (tlb[i].valid && tlb[i].page_number == page_number) {
            *frame_number = tlb[i].frame_number;
            tlb_hit_count++;
            return 1; // 命中
        }
    }
    return 0; // 未命中
}

void tlb_insert(int page_number, int frame_number) {
    tlb[tlb_next_replace].page_number = page_number;
    tlb[tlb_next_replace].frame_number = frame_number;
    tlb[tlb_next_replace].valid = 1;
    tlb_next_replace = (tlb_next_replace + 1) % TLB_SIZE;
}

double tlb_hit_rate() {
    if (tlb_access_count == 0) return 0.0;
    return (double)tlb_hit_count / tlb_access_count;
}

typedef struct {
    int page_number; // 虚拟页号
    int frame_number; // 分配到的物理帧号
    int valid; // 有效位（1=在内存中）
    int dirty; // 脏页位（是否被修改）
    unsigned char *data; // 指向该页数据的缓冲区（256字节）
} PageTableEntry;

PageTableEntry read_page_entry_from_backing_store(int page_number, int frame_number) {
    PageTableEntry entry;
    entry.page_number = page_number;
    entry.frame_number = frame_number;
    entry.valid = 1;
    entry.dirty = 0;
    entry.data = NULL;

    FILE *file = fopen(FILE_NAME, "rb");
    if (file == NULL) {
        perror("Error opening backing_store.bin");
        return entry;
    }

    if (fseek(file, page_number * PAGE_SIZE, SEEK_SET) != 0) {
        perror("Error seeking to page");
        fclose(file);
        return entry;
    }

    unsigned char *buffer = (unsigned char *) malloc(PAGE_SIZE);
    if (buffer == NULL) {
        perror("Memory allocation failed");
        fclose(file);
        return entry;
    }

    size_t bytes_read = fread(buffer, sizeof(unsigned char), PAGE_SIZE, file);
    if (bytes_read != PAGE_SIZE) {
        fprintf(stderr, "Error reading page %d (read %zu bytes)\n", page_number, bytes_read);
        free(buffer);
        fclose(file);
        return entry;
    }

    fclose(file);
    entry.data = buffer;
    return entry;
}

int get_page_number(int number) {
    // 转换为十六进制，取前两位作为页号，将页号转化为十进制后输出
    int page_number = (number >> 8) & 0xFF;
    // 输出16进制的number
    printf("Hexadecimal representation: %02X\n", number);
    return page_number;
}

int get_offset(int number) {
    // 获取低8位作为偏移量
    int offset = number & 0xFF;
    return offset;
}

// 模拟物理内存
unsigned char physical_memory[256][256];

// 模拟页表

typedef struct {
    int frame_number; // 物理帧号
    int valid; // 有效位（1=在内存中）
} PageTable;

PageTable page_table[256];

int get_new_frame_number() {
    // 获取一个新空闲物理帧，按理来说这个函数应当做页面置换的操作，但是此试验的环境中不会有页面置换，所以将页表号看作新的空闲帧
    for (int i = 0; i < 256; i++) {
        if (page_table[i].valid == 0) {
            printf("Get new frame number %d\n", i);
            return i; // 返回第一个空闲的物理帧号
        }
    }
    fprintf(stderr, "No free frame available!\n");
    return -1;
}

// 定义缺页次数与请求页次数
int page_fault_count = 0;
int page_request_count = 0;

void load_page_to_memory(int page_number, int frame_number) {
    if (page_table[page_number].valid == 0) {
        page_fault_count++;
        printf("Page fault: Page %d not in memory, loading...\n", page_number);
        // 执行缺页处理流程：
        // 1. 从 backing_store.bin 加载该页内容
        PageTableEntry entry = read_page_entry_from_backing_store(page_number, frame_number);
        // 2. 找一个物理帧
        int physical_frame_number = get_new_frame_number();
        // 3. 将内容写入帧中
        for (int i = 0; i < PAGE_SIZE; i++) {
            physical_memory[physical_frame_number][i] = entry.data[i];
        }
        // 4. 更新页表：frame_number、valid = 1
        page_table[page_number].frame_number = frame_number;
        page_table[page_number].valid = 1;
        // TLB插入
        tlb_insert(page_number, frame_number);
    } else {
        printf("Hit! Page %d is already in memory.\n", page_number);
    }
}

int main() {
    // 读取addresses.txt的每一行并输出
    init_tlb();
    FILE *file = fopen("addresses.txt", "r");
    if (file == NULL) {
        perror("Error opening addresses.txt");
        return 1;
    }
    // 重复读取直到
    while (1) {
        int address;
        if (fscanf(file, "%d", &address) != 1) {
            break; // 读取失败或到达文件末尾
        }
        page_request_count++; // 每处理一个地址，请求数+1
        // 获取页号和偏移量
        int page_number = get_page_number(address);
        int offset = get_offset(address);
        printf("Address: %d, Page Number: %d, Offset: %d\n", address, page_number, offset);

        int frame_number;
        // 先查TLB
        if (tlb_lookup(page_number, &frame_number)) {
            printf("TLB Hit! Page %d -> Frame %d\n", page_number, frame_number);
        } else {
            // TLB未命中，查页表
            if (page_table[page_number].valid) {
                frame_number = page_table[page_number].frame_number;
                // TLB插入
                tlb_insert(page_number, frame_number);
            } else {
                // 缺页处理
                load_page_to_memory(page_number, page_number);
                frame_number = page_number; // 由于你的实现frame_number=page_number
            }
        }

        printf("Page Faults: %d\n", page_fault_count);
        printf("Page Requests: %d\n", page_request_count);
        printf("Page fault rate: %.2f%%\n",
               (page_fault_count * 100.0) / page_request_count);
        printf("TLB Access: %d, TLB Hits: %d\n", tlb_access_count, tlb_hit_count);
        printf("TLB hit rate: %.2f%%\n", tlb_hit_rate() * 100);
    }
    fclose(file);
    return 0;
}
