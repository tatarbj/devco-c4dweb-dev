<form name="form_modifica_elemento" action="#" method="POST" onsubmit="return false;" id="form_modifica_elemento">
    <label for="id_ele">Id: </label><span id="span_id_ele"></span> 
    <input type="hidden" id="id_ele" name="id_ele"> 
	<input type="hidden" id="colonna_ele" name="colonna_ele"> 
    <input type="hidden" id="vertical" name="vertical" value="1"> 
	<input type="hidden" name="ordine" value="0" id="ordine_ele">


	<label for="titolo">Titolo: </label>
	<!--<input type="text" id="titolo" name="titolo" value="" class="form-control" style="width: 300px ;"> -->
	<textarea id="titolo" name="titolo" class="form-control" style="width: 300px; "></textarea>
	
	<label for="bg_color">Colore di sfondo: </label>
	<div class="input-group">
		<div class="input-group-btn ">
			<button type="button" class="btn btn-default" id="bg_color" style="width: 50px;" name="bg_color">
				<span class="color-fill-icon dropdown-color-fill-icon" style="background-color:#000;"> &nbsp;  &nbsp; </span>
				&nbsp;<b class="caret"></b>
			</button>
			
		</div>
		<input type="text" name="bg_col" class="form-control" style="width: 150px;" id="bg_col" value="">
	</div>
	<br>

	<label for="hovering">Hovering: </label>
	<textarea name="hovering" id="hovering" class="form-control" style="height: 150px;"></textarea>

</form>