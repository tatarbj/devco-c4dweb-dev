<form name="form_modifica_elemento" action="#"  method="POST"  onsubmit="return false;" id="form_modifica_elemento">
    <input type="hidden" id="id_ele" name="id_ele">
	<input type="hidden" id="vertical" name="vertical" value="0">
	<input type="hidden"  name="colonna" id="colonna_ele" value="13">
	<input type="hidden" name="bg_col" class="form-control" style="width: 150px;" id="bg_col">
	
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
	
	<label for="descr">Descrizione: </label>
	<textarea name="descr" id="descr" class="form-control" style="height: 100px;"></textarea>
		
	<label for="hovering">Hovering: </label>
	<textarea name="hovering" id="hovering" class="form-control" style="height: 100px;"></textarea>
</div>
</form>