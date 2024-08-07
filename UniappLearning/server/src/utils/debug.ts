let ifErrorOccurred = false;

class consoleDebug {
    warn(message: string): void {
        console.warn(`\x1b[33m%s\x1b[0m`, message); // Yellow color
    }

    error(message: string): void {
        console.error(`\x1b[31m================================================================\x1b[0m`); // Red color
        console.error(`\x1b[31m|| FATAL ERROR OCCURED, THE PROGRAM MIGHT NOT BE AVALIBLE NOW ||\x1b[0m`); // Red color
        console.error(`\x1b[31m||     PLEASE FIX THE PROBLEM BELOW AND RESTART THE SERVER    ||\x1b[0m`); // Red color
        console.error(`\x1b[31m================================================================\x1b[0m`); // Red color
        console.error(`\x1b[31m[FATAL ERROR] %s\x1b[0m`, message); // Red color
        ifErrorOccurred = true;
    }

    success(message: string): void {
        console.log(`\x1b[92m%s\x1b[0m`, message); // Green color
    }

    log(message: string): void {
        console.log(`\x1b[36m[Log] %s\x1b[0m`, message); // Cyan color
    }

    debug(message: string): void {
        console.log(`\x1b[35m[Debug] %s\x1b[0m`, message); // Magenta color
    }

    conn(message: string): void {
        console.log(`\x1b[34m[Connection] %s\x1b[0m`, message); // Blue color
    }
}
const logger = new consoleDebug();

export {
    logger,
    ifErrorOccurred
}
