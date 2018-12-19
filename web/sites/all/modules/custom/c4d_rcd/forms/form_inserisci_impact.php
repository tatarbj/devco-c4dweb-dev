<form name="form_inserisci_elemento" action="#"  onsubmit="return false;" method="POST" id="form_inserisci_elemento">
<input type="hidden" name="tipologia" value="inpact">
<input type="hidden" name="vertical" value="0">
<input type="hidden" name="id_prj" id="id_prj" value="">

    <input type="hidden"  name="colonna" id="colonna_ele" value="13">
	
	
	<label for="ordine_ele">Ordine: </label>
	<select name="ordine" id="ordine_ele" class="form-control">
		<option value="0">Select</option>
		<?php
		for($x=0;$x<=100;$x++) { 
			echo "<option value=\"{$x}\">$x</option>\n";
		}
		?> 
	</select> 
		
	
	<label for="titolo">Titolo: </label>
	<textarea id="titolo" name="titolo" class="form-control" ></textarea>
	
	<br>
	
	<label for="descr">Descrizione: </label>
	<textarea name="descr" id="descr" class="form-control" style="height: 100px;"></textarea>
		
	<label for="hovering">Hovering: </label>
	<textarea name="hovering" id="hovering" class="form-control" style="height: 100px;"></textarea>

</form>