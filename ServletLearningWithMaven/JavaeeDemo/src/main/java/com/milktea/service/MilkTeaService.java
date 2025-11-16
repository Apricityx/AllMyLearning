package com.milktea.service;

import com.milktea.bean.MilkTea;
import java.util.List;

public interface MilkTeaService {
    List<MilkTea> getAll();
    MilkTea getById(int id);
    void addMilkTea(MilkTea milkTea);
    void updateMilkTea(MilkTea milkTea);
    void deleteMilkTea(int id);
}
