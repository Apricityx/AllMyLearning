package com.milktea.serviceImpl;

import com.milktea.bean.MilkTea;
import com.milktea.dao.MilkTeaDao;
import com.milktea.service.MilkTeaService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class MilkTeaServiceImpl implements MilkTeaService {

    @Autowired
    private MilkTeaDao milkTeaDao;

    @Override
    public List<MilkTea> getAll() {
        return milkTeaDao.findAll();
    }

    @Override
    public MilkTea getById(int id) {
        return milkTeaDao.findById(id);
    }

    @Override
    public void addMilkTea(MilkTea milkTea) {
        milkTeaDao.insert(milkTea);
    }

    @Override
    public void updateMilkTea(MilkTea milkTea) {
        milkTeaDao.update(milkTea);
    }

    @Override
    public void deleteMilkTea(int id) {
        milkTeaDao.delete(id);
    }
}
