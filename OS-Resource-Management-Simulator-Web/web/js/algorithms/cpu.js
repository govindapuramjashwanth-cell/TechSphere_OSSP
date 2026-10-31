window.CPU = (() => {
  function clone(p){return {...p,remaining:p.burst};}
  function schedule(input, algorithm, quantum){
    let ps=input.map(clone).sort((a,b)=>a.arrival-b.arrival || a.id.localeCompare(b.id));
    let time=0, completed=0, gantt=[], firstStart={};
    const add=(id,start,end)=>{if(end<=start)return;if(gantt.length&&gantt[gantt.length-1].id===id)gantt[gantt.length-1].end=end;else gantt.push({id,start,end});};
    if(algorithm==='rr'){
      const q=[];let i=0;
      while(completed<ps.length){while(i<ps.length&&ps[i].arrival<=time)q.push(ps[i++]);if(!q.length){time=ps[i].arrival;continue;}const p=q.shift();if(firstStart[p.id]===undefined)firstStart[p.id]=time;const run=Math.min(quantum,p.remaining);add(p.id,time,time+run);time+=run;p.remaining-=run;while(i<ps.length&&ps[i].arrival<=time)q.push(ps[i++]);if(p.remaining>0)q.push(p);else{p.completion=time;completed++;}}
    }else{
      while(completed<ps.length){const ready=ps.filter(p=>!p.completion&&p.arrival<=time);if(!ready.length){time=Math.min(...ps.filter(p=>!p.completion).map(p=>p.arrival));continue;}let p;if(algorithm==='fcfs')p=ready.sort((a,b)=>a.arrival-b.arrival||a.id.localeCompare(b.id))[0];else if(algorithm==='sjf')p=ready.sort((a,b)=>a.burst-b.burst||a.arrival-b.arrival)[0];else p=ready.sort((a,b)=>a.priority-b.priority||a.arrival-b.arrival)[0];if(firstStart[p.id]===undefined)firstStart[p.id]=time;add(p.id,time,time+p.burst);time+=p.burst;p.remaining=0;p.completion=time;completed++;}
    }
    const rows=ps.map(p=>{const ct=p.completion,tat=ct-p.arrival,wt=tat-p.burst,rt=firstStart[p.id]-p.arrival;return{...p,ct,tat,wt,rt};});
    const avg=k=>rows.reduce((s,p)=>s+p[k],0)/rows.length;
    return {rows,gantt,metrics:{wt:avg('wt'),tat:avg('tat'),rt:avg('rt')}};
  }
  return {schedule};
})();
