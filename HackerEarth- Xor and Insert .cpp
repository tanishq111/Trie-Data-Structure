#include <bits/stdc++.h>
    using namespace std;

    const int ALPHABET_SIZE = 2;

    bool check(int n,int pos)
    {
        return ((bool)(n & (1<<pos)));
    }

    // trie node
    struct TrieNode
    {
        struct TrieNode *children[2];/// one for one and another for zero
    };

    struct TrieNode *getNode(void)
    {
        struct TrieNode *pNode =  new TrieNode;
        for (int i = 0; i < 2; i++)
            pNode->children[i] = NULL;

        return pNode;
    }

    void insert(struct TrieNode *root, int key)
    {
        struct TrieNode *pCrawl = root;
        for (int i = 31; i >=0; i--)
        {
            int index = (int)check(key,i);/// check ,this bit is on or not if on then go index=1 or go index=0
            if (!pCrawl->children[index])
                pCrawl->children[index] = getNode();

            pCrawl = pCrawl->children[index];
        }
    }
    int max_query(int key,struct TrieNode *root)
    {
        struct TrieNode* pCrawl=root;
        int mx_val=0;
        for(int i=31;i>=0;i--)
        {
            int index=check(key,i);
            if(pCrawl->children[index^1])/// when index is 0, then we will choose 1 (0^1)=1 or we will choose 0 when index is 1 (1^1)=0
            {
                mx_val+=(1<<i);/// here xor will give value 1 so take this one
                pCrawl=pCrawl->children[index^1];
            }
            else
            {
                 pCrawl=pCrawl->children[index];/// the index^1 is null , so we have to index
            }
        }
        return (mx_val);
    }

    int min_query(int key,struct TrieNode *root)
    {
        struct TrieNode* pCrawl=root;
        int min_val=0;
        for(int i=31;i>=0;i--)
        {
            int index=check(key,i);
            if(pCrawl->children[index])/// First we will choose , to go as index ,if index is 1 we will go 1 or 0 go o
            {
                pCrawl=pCrawl->children[index];
            }
            else
            {
                min_val+=(1<<i);/// it will cause value ,so take this
                pCrawl=pCrawl->children[index^1];
            }
        }
        return (min_val);
    }


    void delet(struct TrieNode *root)
    {
         for(int i=0;i<ALPHABET_SIZE;i++)
    {
        if(root->children[i])
            delet(root->children[i]);
    }
       delete (root);
    }


    // Driver
    int main()
    {
        ///ios_base::sync_with_stdio(false);
        ///cin.tie(NULL);
        int tc;
        scanf("%d",&tc);
        struct TrieNode *root = getNode();
        int mn=0;
        int prefix_xor=0;
        insert(root,0);/// here we have to check first ,that's why we have created a root node first
        for(int caso=1;caso<=tc;caso++)
        {
        int q,x;
        scanf("%d",&q);
        if(q==1)
        {
            scanf("%d",&x);
            insert(root,prefix_xor^x);
        }
        else if(q==2)
        {
            scanf("%d",&x);
            prefix_xor^=x;
        }
        else
        {
            mn=min_query(prefix_xor,root);
            printf("%d\n",mn);
        }
        ///delet(root);
        }
        return 0;
    }
