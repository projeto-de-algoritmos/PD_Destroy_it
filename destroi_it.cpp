#include<bits/stdc++.h>

using ll = long long;

using namespace std;
ll card_qtd = 0;
// Returns the maximum value that can be put in a knapsack of capacity W 
ll knapSack(ll W, vector <ll> wt, vector <ll> val, ll n) 
{ 
    ll i, w;
    ll K[n+1][W+1]; 
    vector <ll> cards(3);
    // Build table K[][] in bottom up manner 
    for (i = 0; i <= n; i++) 
    { 
        for (w = 0; w <= W; w++) 
        { 
            if (i==0 || w==0) 
                K[i][w] = 0; 
            else if (wt[i-1] <= w) 
                    K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]); 
            else
                    K[i][w] = K[i-1][w]; 
        } 
    } 

// here we find the cards
    ll dam = 0, max_val = 0;
    bool first = true; 
    // stores the result of Knapsack 
    ll res = K[n][W];     
    //prllf("%d\n", res); 
        
    w = W; 
    for (i = n; i > 0 && res > 0; i--) { 
            
        // either the result comes from the top 
        // (K[i-1][w]) or from (val[i-1] + K[i-1] 
        // [w-wt[i-1]]) as in Knapsack table. If 
        // it comes from the latter one/ it means  
        // the item is included. 
        if (res == K[i - 1][w])  
            continue;         
        else { 
            if(first){
                max_val = val[i - 1];
                first =false;
            }

            // This item is included.
            card_qtd++;

            //verify the double dam card and re-add her with double dam
            if(!(card_qtd%10)){
                dam -= max_val;
                dam += max_val * 2;
            }
            dam += val[i-1]; 
            //prllf("%d ", wt[i - 1]); 
                
            // Since this weight is included its  
            // value is deducted 
            res = res - val[i - 1]; 
            w = w - wt[i - 1]; 
        } 
    } 
    return dam;
} 

int main (){
    ios::sync_with_stdio(false);
    ll turns,cards,dam = 0,cardam,carcost;
    vector <ll> wt,val;
    cin >> turns;
    while(turns){
        cin >> cards;
        for(ll i = 0;i<cards;i++){
            cin >> carcost >> cardam;
            val.push_back(cardam);
            wt.push_back(carcost);
        }
        
        dam += knapSack(3,wt,val,cards);

        val.clear();
        wt.clear();
        turns--;
    }

    cout << dam << endl;
    return 0;

}