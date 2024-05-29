export class consoleDebug {
    warning(message: string): void {
        console.warn(`\x1b[33m%s\x1b[0m`, message); // Yellow color
    }

    error(message: string): void {
        console.error(`\x1b[31m%s\x1b[0m`, message); // Red color
    }
}
