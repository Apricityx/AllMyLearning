export function error(message: string) {
    return {
        "status": "error",
        "message": message
    }
}

export function success(message: string) {
    return {
        "status": "success",
        "message": message
    }
}

