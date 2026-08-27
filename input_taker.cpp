#include<bits/stdc++.h>
using namespace std;
class joint
{
    public:
    int id;
    float x;
    float y;
    joint()
    {

    }
};
class member
{
    public:
    int id;
    int start;
    int end;
    member()
    {

    }
};
class special_pt
{
    public:
    int id;
    int type;
    special_pt()
    {

    }
};
class load_force
{
    public:
    int id;
    float x;
    float y;
    load_force()
    {

    }
};
int main()
{
    //tell number of joints, members,special pts,load forces.
    int joints,members,special_pts,loads;
    cin>>joints>>members>>special_pts>>loads;
    // format to represent each joint-(id,x,y)
    // format to represent each member-(id,start_joint_id,end_joint_id)
    // format to represent each special pt-(id of joint on which it is,type of pt)
    // type 1 point  x unknown 
    // type 2 point  y unknown
    // format to represent each load-(id,force_x,force_y)
    //remember the way of giving variables decide the variables answers in final form
    // every joint will accept a set of coefficients
    joint Joint[joints];
    member Member[members];
    special_pt Special_pt[special_pts];
    load_force Load[loads];
    // inputting the diagram
    for(int i=0;i<joints;i++)cin>>Joint[i].id>>Joint[i].x>>Joint[i].y;
    for(int i=0;i<members;i++)cin>>Member[i].id>>Member[i].start>>Member[i].end;
    for(int i=0;i<special_pts;i++)cin>>Special_pt[i].id>>Special_pt[i].type;
    for(int i=0;i<loads;i++)cin>>Load[i].id>>Load[i].x>>Load[i].y;

    int no_of_var=members+special_pts;
    vector<vector<float>>mat(no_of_var,vector<float>(no_of_var+1));
    //let each member ,point and load contribute to the equation
    for(int i=0;i<members;i++)
    {
        int point_of_affect=Member[i].id-1;
        int id_start=Member[i].start;
        int id_end=Member[i].end;
        float hori=Joint[id_start-1].x-Joint[id_end-1].x;
        float vert=Joint[id_start-1].y-Joint[id_end-1].y;
        float length=sqrt(hori*hori+vert*vert);
        //vertical part will be decided by the point on which i am acting
        // horizontal part will be decided by who i am

        //start contribute
        int down=2*(id_start-1);
        mat[down][point_of_affect]=(hori/length);
        mat[down+1][point_of_affect]=(vert/length);
        //end contribute
        down=2*(id_end-1);
        mat[down][point_of_affect]=-(hori/length);
        mat[down+1][point_of_affect]=-(vert/length);
    }
    for(int i=0;i<special_pts;i++)
    {
        int pt_id=2*(Special_pt[i].id-1);
        if(Special_pt[i].type==1)
        mat[pt_id][members+i]=1;
        else
        mat[pt_id+1][members+i]=1;
    }
    for(int i=0;i<loads;i++)   
    {
        int pt_id=2*(Load[i].id-1);
        mat[pt_id][members+special_pts]-=Load[i].x;
        mat[pt_id+1][members+special_pts]-=Load[i].y;
    }
    //Output
    for(int i=0;i<no_of_var;i++)
    {
    for(int j=0;j<no_of_var+1;j++)
    cout<<mat[i][j]<<" ";
    cout<<"\n";
    }
    return 0; 
}
// forces are always outward hence positive force means compression
// negative force means it is under tension