import re

def find_names(lines):
    names = []
    for line in lines:
        if re.search(r"NAME\s(.+)\s/(.*)/", line) is not None :
            name = re.search(r"NAME\s(.+)\s/(.*)/", line)
            if name[2] != '':
                #print(name[2])
                name = name[1]+ ' ' + name[2]
                
            else :
                name = name[1]
            names.append(name.replace(" ","_").replace(",","").replace(";","").replace(".","").lower())
            #print(name)
    return names

def find_sexs(lines):
    sexs = []
    for line in lines:
        if re.search(r"SEX\s(.)", line) is not None :
            sex = re.search(r"SEX\s(.)", line)
            sexs.append(sex[1])
    return sexs

def find_ids(lines):
    ids = []
    for line in lines:
        if re.search(r"RIN MH:I(\d+)", line) is not None :
            id = re.search(r"RIN MH:I(\d+)", line)
            ids.append(int(id[1]))
        if re.search(r"RIN MH:IF(\d+)", line) is not None :
            id = re.search(r"RIN MH:IF(\d+)", line)
            ids.append(int(id[1]))
    return ids


def find_fams(lines):
    itfam = 0
    fams = []
    infam = False
    for line in lines:
        if (re.search(r"HUSB\s\WI(\d+)\W",line) is not None) or (re.search(r"WIFE\s\WI(\d+)\W",line) is not None):
            parent = 0
            if re.search(r"HUSB\s\WI(\d+)\W",line) is not None:
                parent = re.search(r"HUSB\s\WI(\d+)\W",line)
                parent = int(parent[1])

            if re.search(r"WIFE\s\WI(\d+)\W",line) is not None:
                parent = re.search(r"WIFE\s\WI(\d+)\W",line)
                parent = int(parent[1])

            if not infam:
                itfam = itfam + 1
                fams.append([[parent],[]])
                infam = True
            elif infam:
                fams[itfam-1][0].append(parent)
        
        if re.search(r"RIN\sMH\WF",line) is not None:
            infam = False

        if re.search(r"CHIL\s\WI(\d+)\W",line) is not None:
            child = re.search(r"CHIL\s\WI(\d+)\W",line)
            child = int(child[1])
            fams[itfam-1][1].append(child) 

    return fams

def construct(names,sexs,fams):
    answers = [[],[]]
    for family in fams:
        for parent in family[0]:
            for child in family[1]:
                try:
                    if sexs[parent] == 'M':
                        ans = 'father('+names[parent]+','+names[child]+').'
                        answers[0].append(ans)
                        #print(ans)
                    else: 
                        ans = 'mother('+names[parent]+','+names[child]+').'
                        answers[1].append(ans)
                    
                except:
                    print("Dont have item with id "+str(parent) +"or " + str(child))
                
    return answers


        

if __name__ == '__main__':
    lines = []

    with open("tree.ged", "r", encoding="utf-8") as f:
        for line in f:
            lines.append(line)

    names = find_names(lines)
    sexs = find_sexs(lines)
    ids = find_ids(lines)

    names = dict(zip(ids,names))
    sexs = dict(zip(ids,sexs))
    fams = find_fams(lines)
    answers = construct(names,sexs,fams)


    with open("ans.pl","w") as p:
        for answer in answers[0]:
            p.write(answer+'\n')
        for answer in answers[1]:
            p.write(answer+'\n')

   

