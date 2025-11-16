package com.milktea.controller;

import com.milktea.bean.MilkTea;
import com.milktea.service.MilkTeaService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@Controller
@RequestMapping("/milktea")
public class MilkTeaController {

    @Autowired
    private MilkTeaService milkTeaService;

    @GetMapping("/list")
    public String list(Model model) {
        List<MilkTea> list = milkTeaService.getAll();
        model.addAttribute("milkTeas", list);
        return "menu.jsp";
    }

    @PostMapping("/add")
    public String add(MilkTea milkTea) {
        milkTeaService.addMilkTea(milkTea);
        return "redirect:/milktea/list";
    }

    @GetMapping("/edit")
    public String edit(@RequestParam("id") int id, Model model) {
        model.addAttribute("milkTea", milkTeaService.getById(id));
        return "edit.jsp";
    }

    @PostMapping("/update")
    public String update(MilkTea milkTea) {
        milkTeaService.updateMilkTea(milkTea);
        return "redirect:/milktea/list";
    }

    @GetMapping("/delete")
    public String delete(@RequestParam("id") int id) {
        milkTeaService.deleteMilkTea(id);
        return "redirect:/milktea/list";
    }
}
