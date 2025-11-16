package oop.task.exp.e03.kg.editor;

import oop.task.exp.e03.kg.core.Entity;
import oop.task.exp.e03.kg.core.Relationship;

public class RelationshipEditor extends Editor<Relationship> {
    @Override
    public String[] values() {
        Relationship r = this.getTarget();
        return new String[]{r.getName(), r.getAttribute()};
    }

    @Override
    public String[] fieldNames() {
        return new String[]{"名称", "属性"};
    }

    @Override
    public void update(String[] values) {
        Relationship r = this.getTarget();
        r.setName(values[0]);
        r.setAttribute(values[1]);
    }

}
