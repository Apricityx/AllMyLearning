package com.milktea.utils;

import java.util.HashMap;

public class AjaxResult extends HashMap<String, Object> {

    public static AjaxResult success(String msg) {
        AjaxResult result = new AjaxResult();
        result.put("status", "success");
        result.put("message", msg);
        return result;
    }

    public static AjaxResult error(String msg) {
        AjaxResult result = new AjaxResult();
        result.put("status", "error");
        result.put("message", msg);
        return result;
    }
}
