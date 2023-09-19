//Uso de Sheets
var ss = SpreadsheetApp.openById('1amdSPr2BSMVhdIp4OrHkbPMZgQtRGuEmHHQJaVEC58U');
var sheet = SpreadsheetApp.getActiveSheet();
//A1-B1
//Texto-Traducción
//--  =GOOGLETRANSLATE(A1;"EN","ES")
function doPost(e) {
  return ContentService.createTextOutput("Método no Admitido")
}

function doGet(e){
  var read = e.parameter.read;
  var texto = e.parameter.texto;
  aplicarEstilos();
  if (read !== undefined){
    return ContentService.createTextOutput(sheet.getRange('B2').getValue());
  }
  if(read==undefined && texto!==undefined){
    var range = sheet.getRange('A2');
    range.setValue(texto);
    //sheet.appendRow([texto]);
    return ContentService.createTextOutput(texto);
  }
}

function aplicarEstilos(){
  var range = sheet.getRange('A1');
  range.setBackgroundRGB(0,0,0);
  range.setFontColor('white');
  range = sheet.getRange('B1');
  range.setBackgroundRGB(0,0,0);
  range.setFontColor('white');
}