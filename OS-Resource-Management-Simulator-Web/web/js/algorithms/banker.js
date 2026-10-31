window.Banker = (() => {
  function check(allocation, maximum, available){
    const n=allocation.length,m=available.length,need=maximum.map((r,i)=>r.map((v,j)=>v-allocation[i][j]));
    if(maximum.length!==n||maximum.some(r=>r.length!==m)||allocation.some(r=>r.length!==m)||need.some(r=>r.some(v=>v<0)))throw Error('Maximum and Allocation matrices must have the same dimensions, and Maximum cannot be less than Allocation.');
    const work=[...available],finish=Array(n).fill(false),seq=[];let progress=true;while(seq.length<n&&progress){progress=false;for(let i=0;i<n;i++){if(finish[i])continue;if(need[i].every((v,j)=>v<=work[j])){for(let j=0;j<m;j++)work[j]+=allocation[i][j];finish[i]=true;seq.push(i);progress=true;}}}
    return {need, safe:seq.length===n, sequence:seq, work};
  } return {check};
})();
