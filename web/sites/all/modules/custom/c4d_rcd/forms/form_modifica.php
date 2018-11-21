<form name="form_modifica_elemento" action="#"  method="POST"  onsubmit="return false;" id="form_modifica_elemento"> 
<div class="row">
	<div class="col-md-6">
		<input type="hidden" id="id_ele" name="id_ele">
		<input type="hidden" id="vertical" name="vertical" value="0">
		
		<label for="colonna_ele">Area: </label>
		<select name="colonna" id="colonna_ele" class="form-control">
		
		</select> 
		
		
		<label for="ordine_ele">Ordine: </label>
		<select name="ordine" id="ordine_ele" class="form-control">
			<option value="0">Select</option>
			<?php
			for($x=0;$x<=100;$x++){
				echo "<option value=\"{$x}\">$x</option>\n";
			}
			?>
		</select> 
		
		
		<label for="titolo">Titolo: </label>
		<textarea name="titolo" id="titolo" class="form-control" style="height: 100px;"></textarea>
		
		<label for="descr">Descrizione: </label>
		<textarea name="descr" id="descr" class="form-control" style="height: 100px;"></textarea>
	</div>
	
	<div class="col-md-6">

		<label for="bg_color">Colore di sfondo: </label>
		<div class="input-group">
			<div class="input-group-btn">
				<button type="button" class="btn btn-default" id="bg_color" style="width: 50px;" name="bg_color">
					<span class="color-fill-icon dropdown-color-fill-icon" style="background-color:#000;"> &nbsp;  &nbsp; </span>
					&nbsp;<b class="caret"></b> 
				</button> 
			</div>
			<input type="text" name="bg_col" class="form-control" style="width: 150px;" id="bg_col" value="">
		</div>

		<label for="descr">Hovering: </label>
		<textarea name="hovering" id="hovering" class="form-control" style="height: 100px;"></textarea>
	</div>
</div>

<input type="hidden" name="http_type" value="http://">
<input type="hidden" name="link_ele" value="">




</form>