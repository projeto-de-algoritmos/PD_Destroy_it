#include<bits/stdc++.h>

using ll = long long;
using namespace std;

ll card_qtd = 0;
bool boost = false;
vector <pair<ll,ll>> max_cards;
priority_queue <pair<ll,ll>> pq;
priority_queue <ll,vector<ll>,greater<ll>> pinf;

// Returns the maximum value that can be put in a knapsack of capacity W 
ll knapSack(ll W, vector <ll> wt, vector <ll> val, ll n,ll turn) 
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
    ll dam = 0,reduc=-1;
    //bool first = true; 
    // stores the result of Knapsack 
    ll res = K[n][W];

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
            // This item is included.
            card_qtd++; 
            reduc++;

            //verify the double dam card and re-add her with double dam
            if(!(card_qtd%10)){
                if(!pq.empty()){
                    pq = priority_queue<pair<ll,ll>>();
                }
                boost = true;
            }
            pinf.push(val[i - 1]);
            if(boost){
                //first =false;
                pq.push({val[i - 1],card_qtd - n-i});
                if((not (card_qtd%10)) or (turn == 1)){
                    if((turn == 1) and (card_qtd%10))
                        max_cards.pop_back();
                    max_cards.push_back(pq.top());
                }
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
        
        dam += knapSack(3,wt,val,cards,turns);

        val.clear();
        wt.clear();
        turns--;
    }
    ll cont = 0;
    bool reduced = false;
    for(ll i = max_cards.size()-1;i>=0;i--){
        //cout << x << endl;
        dam -= max_cards[i].first;
        dam += max_cards[i].first * 2;
        cont = max_cards[i].second % 10;
        //cout << "eei " << cont <<" e "<< max_cards[i].second << endl;
        while(!pinf.empty()){
            if(max_cards[i].second % 10 == 0 or cont == 0 ){
                //cout << "oiii " << cont <<" e "<< max_cards[i].second << endl;
                break;
            }
            dam -= pinf.top();
            pinf.pop();
            cont--;
            reduced = true;
        }
        if(reduced){
            reduced = false;
            if(card_qtd>0){
                card_qtd -= (card_qtd/10) - 1;
            }
        }

    }

    cout << dam << endl;
    return 0;

}