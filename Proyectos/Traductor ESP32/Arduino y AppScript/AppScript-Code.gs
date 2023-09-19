function doGet(e){
  var texto=e.parameter.texto;
  if(texto!==undefined){
      let traduccion=LanguageApp.translate(texto,'en','es');
    return ContentService.createTextOutput(traduccion);
  }
return ContentService.createTextOutput(123);
}
