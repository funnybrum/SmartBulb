#define PROGMEM ICACHE_RODATA_ATTR

const char CONFIG_PAGE[] PROGMEM = R"=====(
<HTML>
	<HEAD>
      <TITLE>%s smart bulb</TITLE>
	</HEAD>
  <BODY>
    <form action="/settings" method="get">
      %s<br><br>
      <fieldset style='display: inline-block; width: 300px'>
        <legend>some settings</legend>
        Some settings:<br> 
        <input type="text" name="some_settings" value="%f"><br>
        <small><em>1.00 for no correction, [0.8, 1.2]</em></small><br><br>
      </fieldset>
      <br><br>
      <input type="submit" value="Save" style='width: 150px;'>
      &nbsp;&nbsp;&nbsp;
      <a href="/reboot">
        <button type="button" style='width: 150px;'>Restart</button>
      </a>
    </form>
  </BODY>
</HTML>
)=====";

const char GET_JSON[] PROGMEM = R"=====({
  "white":%d,
  "red":%d,
  "green":%d,
  "blue": %d
})=====";