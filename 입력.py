# # # name=input("이름: ")
# # # age=input("나이: ")
# # # email=input("이메일: ")
# # # print("당신의 이름은",name,"입니다")
# # # print("당신의 나이는",age,"입니다")
# # # print("당신의 이메일은",email,"입니다")

# # a =int(input("숫자를 입력하세요: ")) #input은 문자형을 반환하므로 int를 붙임
# # b =int(input("숫자를 입력하세요: "))
# # print("입력하신 값의 합은",a+b)
# # print("입력하신 값의 차는",a-b)
# # print("입력하신 값의 곱은",a*b)
# # #input의 반환형은 무조건 문자형

# # a=float(input("실수입력:"))
# # b=float(input("실수입력:"))
# # print("입력하신 값의 합은",a+b)
# # print("입력하신 값의 차는",a-b)
# # print("입력하신 값의 곱은",a*b)

# # a=int(input("국어점수를 입력하세요: "))
# # b=int(input("수학점수를 입력하세요: "))
# # c=int(input("과학점수를 입력하세요: "))
# # print("당신의 평균점수는", round((a+b+c)/3,2))
# # #반올림 round(숫자,자릿수)

# # apple =3000*int(input("사과는 몇개 사실거에요? "))
# # bear = 2000*int(input("배는 몇개 사실건가요? "))
# # print("고객님께서 지불하셔야할 총 금액은" ,apple+bear)

# hour = 3600*int(input("시간을 입력해주세요: "))
# minute = 60*int(input("분을 입력해주세요: "))
# second = int(input("초를 입력해주세요: "))
# print("총 ", hour+minute+second,"초 입니다.")

# 섭씨 = float(input("섭씨온도를 입력하세요: "))
# 화씨 = 섭씨*9/5+32
# print("화씨온도로 변화하면",화씨,"입니다.")

# num = int(input("숫자를 입력하세요: "))
# hundred = num//100
# ten = num%100//10 #이 방법을 생각못함
# one = num%10
# print("일의자리: ", one)
# print("십의자리: ", ten)
# print("백의자리: " , hundred)

# birthday = int(input("생년월일을 입력하세요: "))
# year = birthday//10000
# month = birthday%10000//100 #birthdy//100%100
# day = birthday%100
# print(year)
# print(month)
# print(day)

total = int(input("총 초를 입력해주세여: "))
hour = total//3600
minute = total%3600//60
second = total%60
print(hour)
print(minute)
print(second)