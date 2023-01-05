
#student class 이다.
class Student:
    def __init__(self, num, name, kor, eng, math, total, avg, order):
        self._num = num
        self._name = name
        self._kor = kor
        self._eng = eng
        self._math = math
        self._total = total
        self._avg = avg
        self._order = order

    # student class의 각 변수를 보호아기 위한 @property 이다.
    @property
    def num(self):
        return self._num

    @property
    def name(self):
        return self._name

    @property
    def kor(self):
        return self._kor

    @property
    def eng(self):
        return self._eng

    @property
    def math(self):
        return self._math

    @property
    def total(self):
        return self._total

    @property
    def avg(self):
        return self._avg

    def get_order(self):
        return self._order
    
    def set_order(self, order):
        self._order = order
    
    order = property(get_order, set_order)
