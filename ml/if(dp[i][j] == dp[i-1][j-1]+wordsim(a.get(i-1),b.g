if(dp[i][j] == dp[i-1][j-1]+wordsim(a.get(i-1),b.get(j-1) && cnt[i][j] > cnt[i-1][j-1]+1){
	path[i][j][0] = i-1;
	path[i][j][1] = j-1;
    cnt[i][j] = cnt[i-1][j-1]+1;
}
if(dp[i][j] == dp[i][j-1]+wordsim("",b.get(j-1)) && cnt[i][j] > cnt[i][j-1]+1){
	path[i][j][0] = i;
	path[i][j][1] = j-1;
	cnt[i][j] = Math.min(cnt[i][j],cnt[i][j-1]+1);
}
if(dp[i][j] == dp[i-1][j]+wordsim(a.get(i-1),"") && cnt[i][j] > cnt[i-1][j]+1){
	path[i][j][0] = i-1;
	path[i][j][1] = j;
	cnt[i][j] = Math.min(cnt[i][j],cnt[i-1][j]+1);
}