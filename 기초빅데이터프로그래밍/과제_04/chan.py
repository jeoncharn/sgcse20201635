
# string을 받아 각 문자의 개수를 count하는 함수이다.
# 예시에서 모든 대문자도 소문자의 count로 취급하는 것을 바탕으로,
# string.lower()을 바탕으로 dict type에 count를 저장한다.

def count(string):
    input_list = list(string.lower())
    dict_count = {}
    
    for i in input_list:
        #만약 이미 count되고 있다면 1을 추가한다.
        if i in dict_count:
            dict_count[i] += 1
            
        #원래 count되지 않은 문자라면, dict_count에 새로 대입한다.
        else:
            dict_count[i] = 1

    for i in dict_count:
        print("({char} : {count})  ".format(char = i, count = dict_count[i]), end = '')
    print("")

# string을 받아, 대문자는 소문자로, 소문자는 대문자로 convert하는 함수이다.
# string을 list로 변환한 이후, 각 원소가 소문자인지, 대문자인지에 따라 변환을 수행한다.

def convert(string):
    input_list = list(string)

    for i in range(0, len(input_list)):
        #만약 원소가 대문자인 경우, 소문자로 변환한 이후 list에 저장한다.
        if input_list[i].isupper():
            input_list[i] = input_list[i].lower()
        
        #소문자인 경우, 대문자로 저장한다.
        elif input_list[i].islower():
            input_list[i] = input_list[i].upper()
    #list를 다시 string으로 바꿔주기 위해 join() method를 사용한다.
    print("".join(input_list))
    


while True:
    #input이 STOP이 아니라면, count, convert 함수를 수행한다.
    string = input("Input:")
    if string != "STOP":    
        count(string)
        convert(string)
        
    #input으로 STOP이 들어오면 Bye를 print하고 종료한다.
    else:
        print("Bye")
        break
