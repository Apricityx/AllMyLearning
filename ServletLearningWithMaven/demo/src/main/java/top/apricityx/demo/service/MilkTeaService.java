package top.apricityx.demo.service;

import top.apricityx.demo.bean.MilkTea;

import java.util.List;

public interface MilkTeaService {
    List<MilkTea> getAll();
    MilkTea getById(int id);
    void addMilkTea(MilkTea milkTea);
    void updateMilkTea(MilkTea milkTea);
    void deleteMilkTea(int id);
}
