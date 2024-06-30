declare module 'consoleDebug' {
    export class consoleDebug {
        warning(message: string): void;
        error(message: string): void;
        success(message: string): void;
        log(message: string): void;
        debug(message: string): void;
        conn(message: string): void;
    }

    // Declare any global variables here if necessary
    export let ifErrorOccurred: boolean;
}