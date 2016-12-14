#include <linux/pagemap.h>
#include <linux/file.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h> 
#include <linux/dcache.h> 
#include <linux/module.h>

#include <linux/init.h>
#include <linux/proc_fs.h>
#include "../../include/linux/seq_file.h"

#include "ElementsSructs.h"
#include "FileLinkedListOperations.h"
#include "PageLinkedListOperations.h"
#include "TransitionLinkedListOperations.h"
#include "TransitionTableOperations.h"



 static int
__do_page_cache_readahead_handler(struct address_space *mapping, struct file *filp,
			pgoff_t offset, unsigned long nr_to_read,
			unsigned long lookahead_size);
static int __init lynx_prediction_init (void);
static void __exit lynx_prediction_exit (void);
TransitionNode *getTransNodeWithBestProba(PageNode *pnode);


extern FileNode *filesListHead ; 

static struct jprobe jprobe__do_page_cache_readahead = {
.entry = __do_page_cache_readahead_handler ,
.kp = {
.symbol_name = "__do_page_cache_readahead" ,
},
};

 static int
__do_page_cache_readahead_handler(struct address_space *mapping, struct file *filp,
			pgoff_t offset, unsigned long nr_to_read,
			unsigned long lookahead_size)
{
  FileNode *fnode=NULL;
  PageNode *pnode=NULL;
  TransitionNode *tnode=NULL;

	  printk(KERN_INFO "\n Readahead is executed on the file : %s\n",filp->f_dentry->d_name.name );
	
	  fnode= filesListHead;
	  if(fnode == NULL){
	    jprobe_return () ;
            return 0;
	  }
	  
	//find the file in the list
	 while ((strcmp(fnode->filename,filp->f_dentry->d_name.name)!=0)&&(GetNextFileNode(fnode)!=NULL))
	 {
	    fnode = GetNextFileNode(fnode);
	 }
	 
	 if(fnode != NULL)
	 {
	   //we found the damn file in the list
	   //look for the page now
	   pnode =fnode->listPage;
	   if(pnode==NULL){
	     jprobe_return () ;
	     return 0;
	   }
	   while ((pnode->pageId != offset )&&( GetNextPageNode(pnode) != NULL))
	    {
	      pnode = GetNextPageNode(pnode);
	    }
	    
	    if(pnode != NULL){
	      //we found the damn page within the list 
	      //find the trans with best porba 
	      tnode = getTransNodeWithBestProba(pnode);
	      if(tnode == NULL) {
		printk(KERN_INFO "\n No prediction is availble \n");
	      }else{
		printk(KERN_INFO "\n The current page is : [%ld], the next page to load is : [%ld], and the proba is : [%ld]/[%ld]\n",offset,tnode->pageId,tnode->transCount,pnode->pageCount);
		
	      }
	    }	   	   
	 }			    
  jprobe_return () ;
  return 0;
}

TransitionNode *getTransNodeWithBestProba(PageNode *pnode){
  TransitionNode *tnode = NULL;
  TransitionNode *bestTnode=NULL;
  tnode = pnode->listTransitions;
  while(tnode !=NULL){
    if(bestTnode==NULL)
     bestTnode=tnode;
    else{
      if(tnode->transCount > bestTnode->transCount)
        bestTnode = tnode;
    }	
    tnode = GetNextTransNode(tnode);    
  }
  
  return bestTnode;
}


static int __init lynx_prediction_init (void)
{
 int res ;
 res = register_jprobe(&jprobe__do_page_cache_readahead ) ; 
 if (res <0)
 {
   printk (KERN_INFO "LYNX : Erreur pose jprobe ...\ n " ) ;
 return -1;
 }
 printk ( KERN_INFO "LYNX : Module LYNX charge \ n " ) ;
 return 0;
}

static void __exit lynx_prediction_exit (void)
{  
 unregister_jprobe(&jprobe__do_page_cache_readahead) ;
 printk(KERN_INFO "LYNX : Module LYNX PREDICTION removed \ n " ) ;
}



module_init(lynx_prediction_init);
module_exit(lynx_prediction_exit);

MODULE_LICENSE("GPL");

