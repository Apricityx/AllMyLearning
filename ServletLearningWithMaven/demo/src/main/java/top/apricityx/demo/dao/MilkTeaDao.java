package top.apricityx.demo.dao;

import top.apricityx.demo.bean.MilkTea;

import java.util.List;

public interface MilkTeaDao {
    List<MilkTea> findAll();
    MilkTea findById(int id);
    int insert(MilkTea milkTea);
    int update(MilkTea milkTea);
    int delete(int id);
}

