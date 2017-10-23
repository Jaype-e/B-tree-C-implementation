#include<bits/stdc++.h>
using namespace std;

struct node{
	int data[10];
	int length;
	struct node* child[10];
	bool type;
};
node* p=NULL;
node* globroot=NULL;
int leaf_size,node_size;

node* init(int x,bool z){
	node* p=new node();
	for(int i=0;i<x+1;i++){
		p->child[i]=NULL;
	}
	p->length=0;
	p->type=z;
	return p;
}
int y=0;
void show(node* p,int a=0){

	if(p!=NULL){
		cout<<"node "<<a<<" :";
		for(int i=0;i<p->length;i++)
			cout<<p->data[i]<<" ";
		cout<<endl;
		
		for(int i=0;i<p->length+1;i++){
			show(p->child[i],a+1);
		}
		cout<<endl;
	}
}


node* insert(int item, node* root){
	if(root==NULL){
		root=init(leaf_size,true);
		root->data[root->length++]=item;
	
		return root;
	}
	else{
		//checking it is already present or not
		int index=lower_bound(root->data,root->data+root->length,item)-root->data;
		if(root->child[index]==NULL ){
			
			if(root->length < leaf_size){
				root->data[root->length++]=item;
				
				sort(root->data,root->data+root->length);
				return root;
			}
			else{
				
				node* s=init(leaf_size,true);
				root->data[root->length++]=item;
				
				sort(root->data,root->data+root->length);
				for(int i=root->length/2;i<root->length;i++){
					s->data[s->length++]=root->data[i];
				}
				globroot=s;
				root->length=root->length/2;
				return root;
			}
		}
		else{
		
			root->child[index]=insert(item,root->child[index]);
			
			if(globroot!=NULL){
				
				if(root->child[index]->type==true){

					int index=lower_bound(root->data,root->data+root->length,globroot->data[0])-root->data;
					if(root->length < node_size){
						for(int i=root->length;i>index;i--){
							root->data[i]=root->data[i-1];
						}
						root->data[index]=globroot->data[0];
						for(int i=root->length+1;i>index+1;i--)
							root->child[i]=root->child[i-1];
						root->child[index+1]=globroot;
						root->length++;
						globroot=NULL;
						return root;
					}
					else{
				
						for(int i=root->length;i>index;i--){
							root->data[i]=root->data[i-1];
						}
						root->data[index]=globroot->data[0];
						root->length++;
						for(int i=root->length;i>index+1;i--)
							root->child[i]=root->child[i-1];
						root->child[index+1]=globroot;
						
						globroot=NULL;

						node* q=init(node_size,false);

						for(int i=root->length/2+1;i<root->length;i++)
							q->data[i-root->length/2-1]=root->data[i];

						for(int i=root->length/2;i<root->length;i++){
							q->child[q->length++]=root->child[i+1];
						}
						q->length--;
						root->length=root->length/2;
						globroot=q;
					
						return root;

					}
				}
				else{

					int index=lower_bound(root->data,root->data+root->length,root->data[root->length])-root->data;
					if(index<node_size){
						for(int i=root->length;i>index;i--){
							root->data[i]=root->data[i-1];
						}
						root->data[index]=globroot->data[0];
						for(int i=root->length+1;i>index+1;i--)
							root->child[i]=root->child[i-1];
						root->child[index+1]=globroot;
						root->length++;
						globroot=NULL;
						return root;
					}
					else{
						for(int i=root->length;i>index;i--){
							root->data[i]=root->data[i-1];
						}
						root->data[index]=globroot->data[0];
						for(int i=root->length+1;i>index+1;i--)
							root->child[i]=root->child[i-1];
						root->child[index+1]=globroot;
						root->length++;
						globroot=NULL;

						node* p=init(node_size,false);

						for(int i=root->length/2+1;i<root->length;i++){
							p->data[p->length]=root->data[i];
							p->child[p->length++]=root->child[i];
						}
						p->child[p->length]=root->child[root->length];
						root->length=root->length/2;
						globroot=p;
						return root;

					}

				}
			}
			else{
				return root;
			}
			
			
		}
	}
}

void insert2(int item){

	 p=insert(item,p);

	if(globroot!=NULL){
		
		if(p->type==true){
			
			node* s=init(node_size,false);
			s->data[s->length++]=globroot->data[0];
			s->child[0]=p;
			s->child[1]=globroot;
			globroot=NULL;
			p=s;
		}
		else{
		

			node* s=init(node_size,false);
			s->data[0]=p->data[p->length-1];
			s->child[0]=p;
			s->child[1]=globroot;
			s->length++;
			globroot=NULL;
			p=s;
		}
	
		
	}

}


int main(){


    leaf_size=3;
    node_size=3;
	insert2(2);
	insert2(3);
	insert2(4);
	insert2(5);
	
	insert2(6);
	
	insert2(7);
	
	insert2(8);
	insert2(9);
	insert2(10);
	insert2(21);

	cout<<"its show time\n";
	y=0;
	show(p);
	
}
