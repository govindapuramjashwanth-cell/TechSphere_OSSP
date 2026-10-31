window.ProcessModel = (() => {
  const states=['NEW','READY','RUNNING','WAITING','TERMINATED'];
  const next={NEW:'READY',READY:'RUNNING',RUNNING:'TERMINATED',WAITING:'READY',TERMINATED:'TERMINATED'};
  function advance(state){return next[state]||'NEW';}
  return {states,advance};
})();
