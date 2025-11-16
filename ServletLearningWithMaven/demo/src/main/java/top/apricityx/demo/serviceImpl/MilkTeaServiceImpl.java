package top.apricityx.demo.serviceImpl;

import top.apricityx.demo.bean.MilkTea;
import top.apricityx.demo.dao.MilkTeaDao;
import top.apricityx.demo.service.MilkTeaService;

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
