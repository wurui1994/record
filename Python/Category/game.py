
nums1 = [1,3,5,7,9,11,13,15]

def baseseq(base,num):
    s = []
    a = num//base
    b = num%base
    s.append(b)
    num = a
    while a > base:
         a = num//base
         b = num%base
         s.append(b)
         num = a
    s.append(a)
    return s

# print(baseseq(3,130))

def basesum(base,seq1,seq2):
    if len(seq1) > len(seq2):
        a = seq1
        b = seq2
    else: 
        a = seq2
        b = seq1
    l = [0]*(len(a)+1)
    for e in range(0,len(b)):
        # print(a,b,e)
        s = a[e] + b[e]
        # print(s)
        l[e] = l[e] + s
    
    for e in range(0,len(l)):
        if l[e] >= base:
            l[e] = l[e] % base
            l[e+1] = l[e+1] +1
    # print(l)
    if l[-1] == 0:
        l.pop()  
    return l


for base in range(2,64):
    # print(base)
    for index1 in nums1:
        nums2 = nums1[nums1.index(index1)+1:]
        # print(index1,nums2)
        for index2 in nums2:
            nums3 = nums2[nums2.index(index2)+1:]
            # print(index2,nums3)
            for index3 in nums3:
                if basesum(base,basesum(base,baseseq(10,index1),baseseq(10,index2)),baseseq(10,index3)) == [0,3]:
                    print(index1,index2,index3,"[base=",base,"]")

                