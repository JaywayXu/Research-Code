import math
import cPickle

fName1 = "measures/pof/POF-nt10-taut10-HE2"
fName2 = "measures/pof/POF-nt10-taut25-HE2"
fName3 = "measures/pof/POF-nt10-taut50-HE2"
fName4 = "measures/pof/POF-nt10-taut5-HE2"
fName5 = "measures/pof/POF-nt1-taut10-HE2"
fName7 = "measures/pof/POF-nt1-taut50-HE2"
fName6 = "measures/pof/POF-nt20-taut10-HE2"
fName8 = "measures/pof/POF-nt20-taut50-HE2"

def printArchive(archive, myFile):
  for kk in archive:
    for ll in kk:
      for mm in ll:
	myFile.write(str(mm))
	myFile.write("\t")
      myFile.write("\n")


def calcHt(tau, nt, taut):
  t=float(1)/float(nt)
  t=t*math.floor(float(tau)/float(taut))
  h=0.75*math.sin(0.5*math.pi*t) + 1.25
  return h

  
for j in range(0, 1001):

    solutions1 = []
    solutions2 = []
    solutions3 = []
    solutions4 = []
    solutions5 = []
    solutions6 = []
    solutions7 = []
    solutions8 = []
    
    archive1 = []
    archive2 = []
    archive3 = []
    archive4 = []
    archive5 = []
    archive6 = []
    archive7 = []
    archive8 = []
    
    for jj in range(0, 1001):

        f1 = float(jj)/float(1000)
        solution = []
                       
        if (((j+1) % 10) == 0):
	  if (j < 200):
	    h=calcHt(j, 10, 10)
	   	    
	    f2 = 1-math.pow(float(math.sqrt(f1)), h) - math.pow(float(f1),h)*math.sin(0.5*math.pi*f1)
	    solution.append(f1)
	    solution.append(f2)
	    
            solutions1.append(solution) 
            solution = []
                        
            h=calcHt(j, 1, 10)
	    
	    f2 = 1-math.pow(float(math.sqrt(f1)), h) - math.pow(float(f1),h)*math.sin(0.5*math.pi*f1)
	    solution.append(f1)
	    solution.append(f2)  
	    
	    solutions5.append(solution)
	    solution = []
	    
	    h=calcHt(j, 20, 10)
	    
	    f2 = 1-math.pow(float(math.sqrt(f1)), h) - math.pow(float(f1),h)*math.sin(0.5*math.pi*f1)
	    solution.append(f1)
	    solution.append(f2)
	    
            solutions6.append(solution)
            solution = []
                       
        if (((j+1) % 25) == 0):
	  if (j < 500):
	    h=calcHt(j, 10, 25)
	    
	    f2 = 1-math.pow(float(math.sqrt(f1)), h) - math.pow(float(f1),h)*math.sin(0.5*math.pi*f1)
	    solution.append(f1)
	    solution.append(f2)
	    
            solutions2.append(solution)
            solution = []
            
        if (((j+1) % 50) == 0):
	    h=calcHt(j, 10, 50)
	    
            f2 = 1-math.pow(float(math.sqrt(f1)), h) - math.pow(float(f1), h)*math.sin(0.5*math.pi*f1)
	    solution.append(f1)
	    solution.append(f2)
	    
            solutions3.append(solution)
            solution = []
            
	    h=calcHt(j, 1, 50)
	    
	    f2 = 1-math.pow(float(math.sqrt(f1)), h) - math.pow(float(f1), h)*math.sin(0.5*math.pi*f1)
	      
	    solution.append(f1)
	    solution.append(f2)
            
            solutions7.append(solution)
            solution = []
            
	    h=calcHt(j, 20, 50)
	    
	    f2 = 1-math.pow(float(math.sqrt(f1)), h) - math.pow(float(f1), h)*math.sin(0.5*math.pi*f1)
	      
	    solution.append(f1)
	    solution.append(f2)
            
            solutions8.append(solution)
            solution = []
            
        if (((j+1) % 5) == 0):
	  if (j < 100):
            
	    h=calcHt(j, 10, 5)
	    
	    f2 = 1-math.pow(float(math.sqrt(f1)), h) - math.pow(float(f1), h)*math.sin(0.5*math.pi*f1)
	      
	    solution.append(f1)
	    solution.append(f2)
	    
            solutions4.append(solution)
            solution = []
    
    if (((j+1) % 10) == 0):
        archive1.append(solutions1)
        archive5.append(solutions5)
        archive6.append(solutions6)
        
        if (j < 200):
         fileName1 = fName1 + "-" + str(j) + ".txt"
	 file1 = open(fileName1, 'w')
	 printArchive(archive1, file1)
	 file1.close()
	
	 fileName5 = fName5 + "-" + str(j) + ".txt"
	 file5 = open(fileName5, 'w')
	 printArchive(archive5, file5)
	 file5.close()

	 fileName6 = fName6 + "-" + str(j) + ".txt"
	 file6 = open(fileName6, 'w')
	 printArchive(archive6, file6)	
	 file6.close()
        
    if (((j+1) % 25) == 0):
        archive2.append(solutions2)
        
        if (j < 500):
         fileName2 = fName2 + "-" + str(j) + ".txt"
	 file2 = open(fileName2, 'w')
	 printArchive(archive2, file2)
	 file2.close()
        
    if (((j+1) % 50) == 0):      
        archive3.append(solutions3)
        
        fileName3 = fName3 + "-" + str(j) + ".txt"
	file3 = open(fileName3, 'w')
	printArchive(archive3, file3)
	file3.close()
	
        archive7.append(solutions7)
        fileName7 = fName7 + "-" + str(j) + ".txt"
	file7 = open(fileName7, 'w')
	printArchive(archive7, file7)
	file7.close()
	
        archive8.append(solutions8)
        fileName8 = fName8 + "-" + str(j) + ".txt"
	file8 = open(fileName8, 'w')
	printArchive(archive8, file8)
	file8.close()
        
    if (((j+1) % 5) == 0):      
        archive4.append(solutions4)
        if (j < 100):        
         fileName4 = fName4 + "-" + str(j) + ".txt"
	 file4 = open(fileName4, 'w')
	 printArchive(archive4, file4)
	 file4.close()










