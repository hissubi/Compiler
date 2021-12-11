void search_tree(Node* topnode)
{
    for(int i = 0; i < topnode->childn; i++)
    {
        Node* tmpnode = topnode->child[i];
        search_tree(tmpnode);
    }


    //modify here------------------------------------------------------
    cout << "data: " << topnode->data << "  child num: " << topnode->childn << endl;
        cout << "\t child: ";
        for(int i = 0; i < topnode->childn; i++)
        {
            Node* tmpnode = topnode->child[i];
            cout << tmpnode->data << " ";
        }
        cout << endl;
//------------------------------------------------------------------------
}
