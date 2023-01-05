class ReadEliminateSignFromPaper:
    def __init__(self, file):
        # chnaging the way of file I/O is possible
        with open(file, 'r', encoding='utf8') as f:
            self.paper = f.readlines() # a list that contains paragraph-wise elements. note: each paragraph has different number of sentences
            
        self.sign_dict = dict() # a dictionary whose key and value are the eliminated sign and the number of that sign, respectively
        
        # divided by . end or /n keyword
        self.sentences = list() # a list that contains sentence-wise elements
        # changing data-type or name of variables above is possible
        
        #########################################################
        # complete the code below, following assignment guideline
        
        self.make_sentences_list()
        
        #########################################################
    
    """it is impossible to change the name of methods (functions) below"""
    def find_eliminate_sign(self, word):
        '''find all signs and eliminate them from given "word"
           (except the period(.) that makes the End Of Sentence)
           and return it
        '''

        no_sign_word = '' # changing this variable also okay
        #########################################################
        # complete the code below, following assignment guideline
        
        for i in range(len(word)):
            if word[i].isalnum() == False:
                if i == len(word)-1 and word[i] == '.':
                    no_sign_word += word[i]
            else:
                no_sign_word += word[i]
        #########################################################
        return no_sign_word
    
    # this function compose self.sentences variable to certain form
    def make_sentences_list(self):
        for paragraph in self.paper:
            para_split = paragraph.split()
            eliminated_data = [self.find_eliminate_sign(word) for word in para_split]
            sentence = ""
            for word in eliminated_data:
                sentence += word
                if word[-1] == '.':
                    self.sentences.append(sentence)
                    sentence = ""
                else:
                    sentence += " "
        
        return None
    
    def get_sorted_sign(self):
        '''return a list 
           that contains (eliminated sign, the number of that sign) tuples 
           and is sorted by the number in descending
        '''
        #########################################################
        # complete the code below, following assignment guideline
    
        for sents in self.paper:
            for word in sents.split():
                    for i in range(len(word)):
                        if word[i].isalnum() == False:
                            if i != len(word)-1 or word[i] != '.':
                                if word[i] not in self.sign_dict:
                                    self.sign_dict[word[i]] = 1
                                else:
                                    self.sign_dict[word[i]] += 1
               
        self.sign_dict = sorted(self.sign_dict.items(), key = lambda item : item[1], reverse = True)
        return self.sign_dict
        #########################################################
    
    def __len__(self):
        '''return the number of sentences'''
        #########################################################
        # complete the code below, following assignment guideline
        # compose sentences variable        
        return len(self.sentences)
        #########################################################
        
    def __getitem__(self, idx):
        """return a sentence that corresponds to the given index "idx" """
        #########################################################
        # complete the code below, following assignment guideline
        return self.sentences[idx]
        #########################################################
