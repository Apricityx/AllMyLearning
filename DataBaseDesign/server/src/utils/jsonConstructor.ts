export function error(extraData?: any) {
    return {
        "status": "error",
        ...extraData
    }
}

export function success(extraData?: any) {
    return {
        "status": "success",
        ...extraData
    }
}

