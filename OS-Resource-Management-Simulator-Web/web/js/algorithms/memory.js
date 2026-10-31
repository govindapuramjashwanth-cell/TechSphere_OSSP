window.Memory = (() => {
  function allocate(blocks, requests, method){
    const remaining=[...blocks]; const out=[];
    requests.forEach((req,i)=>{let candidates=remaining.map((v,j)=>({v,j})).filter(x=>x.v>=req);if(!candidates.length){out.push({id:`P${i+1}`,request:req,block:'—',remaining:'—',ok:false});return;}let pick;if(method==='first')pick=candidates[0];else if(method==='best')pick=candidates.sort((a,b)=>a.v-b.v)[0];else pick=candidates.sort((a,b)=>b.v-a.v)[0];remaining[pick.j]-=req;out.push({id:`P${i+1}`,request:req,block:`B${pick.j+1}`,remaining:remaining[pick.j],ok:true});});
    const total=blocks.reduce((a,b)=>a+b,0), used=blocks.reduce((a,b)=>a+b,0)-remaining.reduce((a,b)=>a+b,0);return {out,remaining,util:total?used/total*100:0};
  } return {allocate};
})();
