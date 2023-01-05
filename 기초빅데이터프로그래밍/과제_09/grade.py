
#student grading system class 이다.
class StudentGradingSystem:
    def __init__(self):
        # 각 instance는 학생의 data를 list로 저장한다.
        self.student_data = []
        
        self.total_avg = 0
        self.kor_avg = 0
        self.eng_avg = 0
        self.math_avg = 0
        
        self.kor_max = 0
        self.eng_max = 0
        self.math_max = 0
        
    def register_student(self, new_student):
        (self.student_data).append(new_student)
    
    #class가 저장하고 있는 학생들을 바탕으로 정보들을 계산하는 method 이다.
    def process(self):
        
        # total을 기준으로 정렬한다.
        self.student_data = sorted(self.student_data, key = lambda x : x.total, reverse = True)
        
        # 학생의 등수를 계산하며, loop를 통해 평균 점수들을 계산한다.
        self.student_data[0].order = 1
        self.total_avg = self.student_data[0].total
        self.kor_avg = self.student_data[0].kor
        self.eng_avg = self.student_data[0].eng
        self.math_avg = self.student_data[0].math
        
        self.kor_max = self.student_data[0].kor
        self.eng_max = self.student_data[0].eng
        self.math_max = self.student_data[0].math
        
        for i in range(1, len(self.student_data)):
            if self.student_data[i].total == self.student_data[i-1].total:
                self.student_data[i].order = self.student_data[i-1].order
            
            else:
                self.student_data[i].order = i + 1
                
            self.total_avg += self.student_data[i].total
            self.kor_avg += self.student_data[i].kor
            self.eng_avg += self.student_data[i].eng
            self.math_avg += self.student_data[i].math
            
            self.kor_max = max(self.student_data[i].kor, self.kor_max)
            self.eng_max = max(self.student_data[i].eng, self.eng_max)
            self.math_max = max(self.student_data[i].math, self.math_max)
    
        self.total_avg = self.total_avg/len(self.student_data)
        self.kor_avg = self.kor_avg/len(self.student_data)
        self.eng_avg = self.eng_avg/len(self.student_data)
        self.math_avg = self.math_avg/len(self.student_data)
    
    def print_students(self):
        for i in self.student_data:
            print(f"번호: {i.num}, 이름: {i.name}, 국어: {i.kor}, 영어: {i.eng}, 수학: {i.math}, 총점: {i.total}, 평균: {i.avg : .2f}, 등수: {i.order}")
        print()
        
    def print_class_information(self):
        
        print(f"총점 반평균: {self.total_avg : .2f}")
        print(f"국어 반평균: {self.kor_avg : .2f}")
        print(f"영어 반평균: {self.eng_avg : .2f}")
        print(f"수학 반평균: {self.math_avg : .2f}")
        print()
        
        print("각 과목의 최고점과 명단")
        
        print(f"국어의 최고점 {self.kor_max}, ", end = "")
        for i in self.student_data:
            if i.kor == self.kor_max:
                print(i.name, end = " ")
        print()
        
        print(f"영어의 최고점 {self.eng_max}, ", end = "")
        for i in self.student_data:
            if i.eng == self.eng_max:
                print(i.name, end = " ")
        print()
        
        print(f"수학의 최고점 {self.math_max}, ", end = "")
        for i in self.student_data:
            if i.math == self.math_max:
                print(i.name, end = " ")
        print()
