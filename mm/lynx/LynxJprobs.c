#include <linux/pagemap.h>
#include <linux/file.h>
# include <linux/kernel.h>
# include <linux/module.h>
# include <linux/kprobes.h> 
# include <linux/dcache.h> 
#include "ElementsSructs.h"
#include "FileLinkedListOperations.h"
#include "PageLinkedListOperations.h"
#include "TransitionLinkedListOperations.h"
#include "TransitionTableOperations.h"



 FileNode *filesListHead = NULL;
  FileNode *currentFileNode = NULL;
  PageNode *currentPageNode = NULL;
  int sourcePage = -1;
  int destinationPage = -1;

int filemap_fault_handler(struct vm_area_struct *vma, struct vm_fault *vmf)
{
  struct file *file = vma->vm_file;
  
printk(KERN_INFO "Lynx: filemap_fault is executed\n") ;

       printk(KERN_INFO "LYNX: requested fils %s \n",file->f_dentry->d_name.name);
       printk(KERN_INFO "LYNX: requested paGe %lu \n",vmf->pgoff);
       currentFileNode = insertFileNode(&filesListHead , file->f_dentry->d_name.name);
       destinationPage = vmf->pgoff; //to do : change int to ul
       insertInTransitionTable(currentFileNode , sourcePage, destinationPage);
       destinationPage = sourcePage;


jprobe_return () ;
return 0;
}

static struct jprobe jprobe_filemap_fault = {
.entry = filemap_fault_handler ,
.kp = {
.symbol_name = "filemap_fault" ,
},
};

static int __init lynx_init (void)
{
 int res ;
 res = register_jprobe(&jprobe_filemap_fault ) ; 
 if (res <0)
 {
   printk (KERN_INFO "LYNX : Erreur pose jprobe ...\ n " ) ;
 return -1;
 }
 printk ( KERN_INFO "LYNX : Module M2LSE charge \ n " ) ;
 return 0;
}

static void __exit Lynx_exit (void)
{
 unregister_jprobe(&jprobe_filemap_fault) ;
 printk(KERN_INFO "LYNX : Module Lynx decharge \ n " ) ;
}

module_init(lynx_init);
module_exit(Lynx_exit);

MODULE_LICENSE("GPL");

