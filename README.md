# Sparse-Matrixes
Sparse Matrix Management app  


The app was a challenge to be done in the name of learning objective approach to programming and app data management  

Whole app is decomposed into three layers:  

CSparseMatrix - logical layer, defines class representing Sparse Matrix  
CSparseMatrixManager - processing layer between interface and logic, contains vector of Sparse Matrix objects  
Interface - UI layer, cli user interface methods only  

CLI commands:  
addmat [dimNum] [dim0size] [dim1size]... [dimNum-1size] [def] <!name!> - creates matrix with [dimNum] dimensions, each one must have   specified [dimXsize], [def] is default value, created matrix will be filled with those values, [name] value is optional and it stands for matrix name   
def [MNr] [dim0] [dim1]… [dimNum-1] [val] - sets [val] to specified matrix in place specified with [dimX] attributes  
list - show list of created matrixes in a certain way [MNr] - [name] size: [dimSizes]  
del [MNr] - deletes matrix with specified number   
delall - deletes all created matrixes  
print [MNr] - prints matrix with specified [MNr]  
clone [MNr] - clones matrix with specified [MNr]  
rename [MNr] [name] - sets new [name] to matrix with specified [MNr]  
quit - cleanse the memory and quits app  


[MNr] of matrixes can be read from the list << essential to manage matrixes  
