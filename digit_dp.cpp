// sum of digit till value
ll dp[20][1000][2],sz;
string v;
// take the value in string v. to_string(value) and size to sz
ll digitsum(ll curr,ll val,bool lagse)
{
    if(curr == sz) return val;
    if(dp[curr][val][lagse]!=-1) return dp[curr][val][lagse];
    ll sum = 0;
    if(lagse)
    {
        for(ll i = 0;i<v[curr] - '0';i++)
        {
            sum+=digitsum(curr+1,i+val,false);
        }
        ll x = v[curr] - '0';
        sum+=digitsum(curr+1,x + val,1);
    }
    else
    {
        for(ll i = 0;i<=9;i++)
        {
            sum +=digitsum(curr+1,i+val,lagse);
        }
    }
    return dp[curr][val][lagse] = sum;
}
