import re
names=[]
sexes=[]
chils= {}
ids = []
husb = False
husb_id = 0
wife = False
wife_id= 0
lines = []
with open("tree.ged", "r", encoding="utf-8") as f:
    lines = f.readlines()
for line in lines:
     
    if re.search(r"GIVN\s(.+)", line) is not None :
        name = re.search(r"GIVN\s(.+)", line)
        names.append(name[1])
        
    if re.search(r"RIN MH:I(\d+)", line) is not None :
        idp = re.search(r"RIN MH:I(\d+)", line)
        ids.append(idp[1])
      
    if re.search(r"SEX\s(.+)", line) is not None :
        sex = re.search(r"SEX\s(.+)", line)
        sexes.append(sex[1])

    if re.search(r'HUSB',line) is not None:
        husb = True
        husb_id = re.search(r'HUSB\s\WI(\d+)\W',line)
        husb_id = husb_id[1]
        chils[husb_id] = []
    
    if re.search(r'WIFE',line) is not None:
        wife = True
        wife_id = re.search(r'WIFE\s\WI(\d+)\W',line)
        wife_id = wife_id[1]
        chils[wife_id] = []

    if re.search(r'RIN\sMH\WF',line) is not None:
        wife = False
        husb = False

    if re.search(r'CHIL\s\WI(\d+)\W',line) is not None:
        child_id = re.search(r'CHIL\s\WI(\d+)\W',line)[1]
        if husb :
            chils[husb_id].append(child_id)
        if wife :
            chils[wife_id].append(child_id)


names = dict(zip(ids,names))
sexes = dict(zip(ids,sexes))

ans = []
male = []
female = []


for par, kids in chils.items():
    for kid in kids:
        ans.append('child('+names[kid]+','+names[par]+').')

for idp in ids:
    if sexes[idp] == 'M':
        male.append('male('+names[idp]+').')
    if sexes[idp] == 'F':
        female.append('female('+names[idp]+').')


ans = ans + male + female
    
with open("gods.pl","w") as p:
    for a in ans:
        p.write(a+'\n')




       
#print(names)
#print(sexes)
print(chils)
print(ans)
#print(lines)


        
       
