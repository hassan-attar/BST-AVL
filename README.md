
# Project Overview

This project features implementations of Binary Search Trees (BST) and AVL Trees in C++.

>**Check out the sample runs at the end of the file**

### **Binary Search Tree (BST)**

The `BST` class provides a foundational implementation of a binary search tree, supporting operations such as insertion, deletion, and search. Key functionalities include:

- **Insertion and Removal**: Methods to insert and remove nodes while maintaining the binary search tree properties.
- **Traversal**: Provides various traversal methods, including Morris traversal for O(n) time and O(1) space complexity, as well as stack-based traversal methods.
- **Height and Size Calculations**: Methods to compute the height and size of the tree.
- **Iterators**: Implements forward and reverse iterators to support traversal in different orders.

### **AVL Tree**

The `AVL` class extends the `BST` class to provide a self-balancing binary search tree. The AVL tree ensures that the height of the tree remains balanced, which guarantees O(log n) time complexity for insertions and deletions. Key features include:

- **Rotations**: Implements left and right rotations to maintain tree balance after insertions and deletions.
- **Balancing**: Utilizes balance factors and rotations to fix imbalances and maintain AVL tree properties.
- **Imbalance Handling**: Supports handling of left-left, right-right, left-right, and right-left imbalances.

### **Design Highlights**

- **Modularity**: The design separates BST and AVL tree functionalities, allowing for clean extensions and modifications.
- **Efficiency**: Emphasizes efficient operations with considerations for space and time complexity.
- **Iterators and Traversal**: Provides flexible tree traversal options through iterators and various traversal techniques.

This project is ideal for understanding fundamental and advanced tree data structures and their applications in maintaining balanced search performance.

# AVL Tree Sample Run (Height Balancing)
<pre>
> Empty AVL tree created. 
> Inserting 50 
50(0)
> Inserting 60 
      50(1)                   
         --\            
            60(0)       
 
 
> Inserting 70
@@RR Imbalance Detected@@
**Performing Left Rotation on node 50**
      60(0)                   
      /----\            
 50(0)      70(0)       
 
 
> Inserting 80 
                  60(1)                                           
            /----------------\                        
       50(0)                  70(1)                   
                                 --\            
                                    80(0)       
 
 
> Inserting 90 
@@RR Imbalance Detected@@
**Performing Left Rotation on node 70**
                  60(1)                                           
            /----------------\                        
       50(0)                  80(0)                   
                              /----\            
                         70(0)      90(0)       
 
 
> Inserting 91 
@@RR Imbalance Detected@@
**Performing Left Rotation on node 60**
                  80(0)                                           
            /----------------\                        
       60(0)                  90(1)                   
      /----\                     --\            
 50(0)      70(0)                   91(0)       
 
 
> Inserting 71 
                                          80(-1)                                                                                          
                        /----------------------------------------\                                                
                   60(1)                                          90(1)                                           
            /----------------\                                       --------\                        
       50(0)                  70(1)                                           91(0)                   
                                 --\                                                            
                                    71(0)                                                       
 
 
> Inserting 72 
@@RR Imbalance Detected@@
**Performing Left Rotation on node 70**
                                          80(-1)                                                                                          
                        /----------------------------------------\                                                
                   60(1)                                          90(1)                                           
            /----------------\                                       --------\                        
       50(0)                  71(0)                                           91(0)                   
                              /----\                                                            
                         70(0)      72(0)                                                       
 
 
> Inserting 73 
@@RR Imbalance Detected@@
**Performing Left Rotation on node 60**
                                          80(-1)                                                                                          
                        /----------------------------------------\                                                
                   71(0)                                          90(1)                                           
            /----------------\                                       --------\                        
       60(0)                  72(1)                                           91(0)                   
      /----\                     --\                                                            
 50(0)      70(0)                   73(0)                                                       
 
 
> Inserting 39 
@@LL Imbalance Detected@@
**Performing Right Rotation on node 80**
                                          71(0)                                                                                           
                        /----------------------------------------\                                                
                  60(-1)                                          80(0)                                           
            /----------------\                              /----------------\                        
      50(-1)                  70(0)                    72(1)                  90(1)                   
      /--                                                --\                     --\            
 39(0)                                                      73(0)                   91(0)       
 
 
> Removing 71 
@@LL Imbalance Detected@@
**Performing Right Rotation on node 60**
                                          70(1)                                                                                           
                        /----------------------------------------\                                                
                   50(0)                                          80(0)                                           
            /----------------\                              /----------------\                        
       39(0)                  60(0)                    72(1)                  90(1)                   
                                                         --\                     --\            
                                                            73(0)                   91(0)       
 
 
> Removing 90 
                                          70(1)                                                                                           
                        /----------------------------------------\                                                
                   50(0)                                          80(-1)                                          
            /----------------\                              /----------------\                        
       39(0)                  60(0)                    72(1)                  91(0)                   
                                                         --\                                    
                                                            73(0)                               
 
 
> Removing 60 
                                          70(1)                                                                                           
                        /----------------------------------------\                                                
                  50(-1)                                          80(-1)                                          
            /--------                                       /----------------\                        
       39(0)                                           72(1)                  91(0)                   
                                                         --\                                    
                                                            73(0)                               
 
 
> Inserting 74 
@@RR Imbalance Detected@@
**Performing Left Rotation on node 72**
                                          70(1)                                                                                           
                        /----------------------------------------\                                                
                  50(-1)                                          80(-1)                                          
            /--------                                       /----------------\                        
       39(0)                                           73(0)                  91(0)                   
                                                      /----\                                    
                                                 72(0)      74(0)                               
 
 
> Inserting 71 
@@LL Imbalance Detected@@
**Performing Right Rotation on node 80**
                                          70(1)                                                                                           
                        /----------------------------------------\                                                
                  50(-1)                                          73(0)                                           
            /--------                                       /----------------\                        
       39(0)                                          72(-1)                  80(0)                   
                                                      /--                     /----\            
                                                 71(0)                   74(0)      91(0)       
 
 
> Inserting 93 
@@RR Imbalance Detected@@
**Performing Left Rotation on node 70**
                                          73(0)                                                                                           
                        /----------------------------------------\                                                
                   70(0)                                          80(1)                                           
            /----------------\                              /----------------\                        
      50(-1)                  72(-1)                   74(0)                  91(1)                   
      /--                     /--                                                --\            
 39(0)                   71(0)                                                      93(0)       
 
 
> Inserting 92 
@@RL Imbalance Detected@@
**Performing Right Rotation on node 93**
**Performing Left Rotation on node 91**
                                          73(0)                                                                                           
                        /----------------------------------------\                                                
                   70(0)                                          80(1)                                           
            /----------------\                              /----------------\                        
      50(-1)                  72(-1)                   74(0)                  92(0)                   
      /--                     /--                                             /----\            
 39(0)                   71(0)                                           91(0)      93(0)       
 
 
> Inserting 94 
@@RR Imbalance Detected@@
**Performing Left Rotation on node 80**
                                          73(0)                                                                                           
                        /----------------------------------------\                                                
                   70(0)                                          92(0)                                           
            /----------------\                              /----------------\                        
      50(-1)                  72(-1)                   80(0)                  93(1)                   
      /--                     /--                     /----\                     --\            
 39(0)                   71(0)                   74(0)      91(0)                   94(0)       
 

Process finished with exit code 0


</pre>

# BST Sample Run
<pre>
> Empty BST created. 
> Inserting 511
511
> Inserting 411
      511                     
    /---                
 411                    
 
 
> Inserting 155
                  511                                             
          /---------                                  
       411                                            
    /---                                        
 155                                            
 
 
> Removing 511
      411                     
    /---                
 155                    
 
 
> Inserting 711
      411                     
    /------\            
 155        711         
 
 
> Inserting 290
                  411                                             
          /------------------\                        
       155                    711                     
        ---\                                    
            290                                 
 
 
> Inserting 510
                  411                                             
          /------------------\                        
       155                    711                     
        ---\                /---                
            290          510                    
 
 
> Inserting 310
                                          411                                                                                             
                      /------------------------------------------\                                                
                   155                                            711                                             
                    ---------\                            /---------                                  
                              290                      510                                            
                                ---\                                                            
                                    310                                                         
 
 
> Inserting 150
                                          411                                                                                             
                      /------------------------------------------\                                                
                   155                                            711                                             
          /------------------\                            /---------                                  
       150                    290                      510                                            
                                ---\                                                            
                                    310                                                         
 
 
> Inserting 120
                                          411                                                                                             
                      /------------------------------------------\                                                
                   155                                            711                                             
          /------------------\                            /---------                                  
       150                    290                      510                                            
    /---                        ---\                                                            
 120                                310                                                         
 
 
> Inserting 160
                                          411                                                                                             
                      /------------------------------------------\                                                
                   155                                            711                                             
          /------------------\                            /---------                                  
       150                    290                      510                                            
    /---                    /------\                                                            
 120                     160        310                                                         
 
 
> Inserting 710
                                          411                                                                                             
                      /------------------------------------------\                                                
                   155                                            711                                             
          /------------------\                            /---------                                  
       150                    290                      510                                            
    /---                    /------\                    ---\                                    
 120                     160        310                     710                                 
 
 
> Inserting 151
                                          411                                                                                             
                      /------------------------------------------\                                                
                   155                                            711                                             
          /------------------\                            /---------                                  
       150                    290                      510                                            
    /------\                /------\                    ---\                                    
 120        151          160        310                     710                                 
 
 
> Inserting 450
                                          411                                                                                             
                      /------------------------------------------\                                                
                   155                                            711                                             
          /------------------\                            /---------                                  
       150                    290                      510                                            
    /------\                /------\                /------\                                    
 120        151          160        310          450        710                                 
 
 
> Inserting 800
                                          411                                                                                             
                      /------------------------------------------\                                                
                   155                                            711                                             
          /------------------\                            /------------------\                        
       150                    290                      510                    800                     
    /------\                /------\                /------\                                    
 120        151          160        310          450        710                                 
 
 
> Inserting 750
                                          411                                                                                             
                      /------------------------------------------\                                                
                   155                                            711                                             
          /------------------\                            /------------------\                        
       150                    290                      510                    800                     
    /------\                /------\                /------\                /---                
 120        151          160        310          450        710          750                    
 
 
> Inserting 850
                                          411                                                                                             
                      /------------------------------------------\                                                
                   155                                            711                                             
          /------------------\                            /------------------\                        
       150                    290                      510                    800                     
    /------\                /------\                /------\                /------\            
 120        151          160        310          450        710          750        850         
 
 

Process finished with exit code 0
</pre>