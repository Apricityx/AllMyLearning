import ast


def main(arg1: str) -> dict:
    string_list = '["a","b","c","d"]'  # 修改这里，使用双引号将元素括起来
    python_list = ast.literal_eval(string_list)
    print(python_list)
    return {
        "result": python_list[0]
    }
