def optimal_merge(files, k):
    heap = build_min_heap(files)
    
    # 填充虚节点
    while (len(heap) - 1) % (k - 1) != 0:
        push(heap, 0) 

    while len(heap) > 1:
        group = []
        for i in range(k):
            group.append(pop(heap))
            
        merged_file = sum(group)
        print("Merging:", group)
        
        push(heap, merged_file)

