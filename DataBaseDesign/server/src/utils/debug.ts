export class consoleDebug {
    warning(message: string): void {
        console.warn(`\x1b[33m%s\x1b[0m`, message); // Yellow color
    }

    error(message: string): void {
        console.error(`\x1b[31m%s\x1b[0m`, message); // Red color
    }

    success(message: string): void {
        console.log(`\x1b[92m%s\x1b[0m`, message); // Green color
    }

    log(message: string): void {
        console.log(`\x1b[36m%s\x1b[0m`, message); // Cyan color
    }
}
