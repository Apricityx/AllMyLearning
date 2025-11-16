def main(arg1: str) -> dict:
    text = "<output>[machine learning, neural networks, data science, robotics, natural language processing]</output>"
    start_index = text.find('<output>[') + 9
    end_index = text.find(']</output>')
    keywords_string = text[start_index:end_index]
    keywords_list = keywords_string.split(', ')

    word1 = keywords_list[0]
    word2 = keywords_list[1]
    word3 = keywords_list[2]
    word4 = keywords_list[3]
    word5 = keywords_list[4]

    return {
        "result": "[" + '"' + word1 + '"' + ", " + '"' + word2 + '"' + ", " + '"' + word3 + '"' + ", " + '"' + word4 + '"' + ", " + '"' + word5 + '"' + "]"
    }