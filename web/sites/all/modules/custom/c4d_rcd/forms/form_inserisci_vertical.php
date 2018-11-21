<form name="form_inserisci_elemento" action="#"  onsubmit="return false;" method="POST" id="form_inserisci_elemento">
	<input type="hidden" name="tipologia" value="vertical">
	<input type="hidden" name="id_prj" id="id_prj" value="">
	<input type="hidden" name="vertical" value="1">
	<input type="hidden" name="ordine" value="0">
	
	<label for="titolo">Titolo: </label>
	<!-- <input type="text" id="titolo" name="titolo" value="" class="form-control" style="width: 300px ;"> -->
	<textarea id="titolo" name="titolo" class="form-control" style="width: 300px; "></textarea>
	
	<br>
	
	<label for="bg_color">Colore di sfondo: </label>
	<div class="input-group">
		<div class="input-group-btn">
			<button type="button" class="btn btn-default" id="bg_color" style="width: 50px;" name="bg_color">
				<span class="color-fill-icon dropdown-color-fill-icon" style="background-color:#000;"> &nbsp;  &nbsp; </span>
				&nbsp;<b class="caret"></b>
			</button>
		</div>
		<input type="text" name="bg_col" class="form-control" style="width: 150px;" id="bg_col">
	</div>
	<br>
	
	
	<label for="hovering">Hovering: </label>
	<textarea name="hovering" id="hovering" class="form-control" style="height: 150px;"></textarea>
</form>