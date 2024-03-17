function result = AHP(num)
    len = length(num);
        temp = 1;
        for i = 2:len
            for j = 1:temp
                num(i,j) = 1/num(j,i);
            end
            temp = temp + 1;
        end
    function result = ifOK(num)
        result = 1;
        disp(num)
        %补全矩阵
        disp(num)
        [x__,y__] = eig(num)
        character = max(diag(y__))
        disp("character")
        level = length(num)
        CI = (character - level)/(level - 1)
        RI = [0,0,0.58,0.90,1.12,1.24,1.32,1.41,1.45,1.49]
        CR = CI/RI(level)
        if CR < 0.1
            result = 1;
        else
            result = 0;
        end
    end

    result = 0;
    if ifOK(num) == 1
        disp("一致性检验通过！")
        disp(num)
        wights = zeros(1,len);
        disp(wights)
        for i = 1:len
            wights(i) = prod(num(i,:))^(1/len); % 这行代码的意思是：第i行的所有元素相乘，然后开len次方
        end 
        wights = wights/sum(wights);
        %计算权重
        disp(wights)
    else
        disp("一致性检验未通过！")
    end
end