import re
import math
try:
    from time import clock
except ImportError:
    from time import perf_counter as clock

pattern = re.compile(r'[^-\w\t\u4e00-\u9fa5]') 

word_split = lambda s:" ".join(pattern.split(s.strip())).strip().split()

def count(worddict,words):
    for word in words:
        if word in worddict.keys():
            worddict[word] += 1
        else:
            worddict[word]  = 1
    return worddict

def count_word_in_sentences2(sentences):
    worddict = {}
    for sentence in sentences:
        worddict = count(worddict,list(set(word_split(sentence))))
    return worddict

if __name__ == '__main__':
    file = open('paper.txt', 'rt', encoding='utf-8')
    data = file.read()
    data = data.replace('\n', '').replace('，', '')

    sentences = data.split('。')
    # sentences.remove('')
    words = word_split(data)

    # 1.计算每个单词在整篇中出现的次数
    worddict = {}
    worddict = count(worddict,words)

    # 2.计算每个单词在句子列表中出现的次数
    wordset = worddict.keys()  # 去重，获取单词集合

    st = clock()
    words_in_sentences = count_word_in_sentences2(sentences)
    et = clock()
    print(et - st)
    
    print(len(wordset),len(sentences))
 
    total = {word:1.0*worddict[word]/len(words)*math.log2(len(sentences)/(words_in_sentences[word])) for word in wordset}
        
    sort_total = sorted(total.items(), key = lambda item: item[1], reverse=True)
    
    string = ['%.3e'%v + '\t' + k + '\n' for k,v in sort_total]
    output = open('output.txt', 'w')
    output.writelines(string)
    output.close()