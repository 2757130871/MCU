

// 需要考虑大数问题
//
//利用字符串模拟整数加法运算
//注意细节
//
//

class Solution {
public:

    void swap(char& c1, char& c2)
    {
        char tmp = c1;
        c1 = c2;
        c2 = tmp;
    }

    string addStr(string num1, string num2)
    {
        string str;
        int begin1 = 0, end1 = num1.size() - 1;
        int begin2 = 0, end2 = num2.size() - 1;

        int carry = 0;
        while (end1 >= begin1 && end2 >= begin2)
        {
            int tmp = (num1[end1] - '0') + (num2[end2] - '0') + carry;
            if (tmp > 9)
            {
                str += (tmp % 10) + '0';
                carry = 1;
            }
            else
            {
                str += tmp + '0';
                carry = 0;
            }

            end1--;
            end2--;
        }

        while (end1 >= begin1)
        {
            int tmp = num1[end1] - '0' + carry;

            if(tmp > 9)
            {
                str += tmp % 10 + '0';
                carry = 1;
            }
            else
            {
                str += tmp + '0';
                carry = 0;
            }

            end1--;
        }

        while (end2 >= begin2)
        {
            int tmp = num2[end2] - '0' + carry;

            if(tmp > 9)
            {
                str += tmp % 10 + '0';
                carry = 1;
            }
            else
            {
                str += tmp + '0';
                carry = 0;
            }

            end2--;
        }

        if(carry)
            str += '1';
      
        //反转
        int begin = 0, end = str.size() - 1;
        while (begin < end)
        {
            swap(str[begin], str[end]);
            begin++;
            end--;
        }

        return str;
    }

    string addStrings(string num1, string num2) {

        return addStr(num1, num2);
    }
};
