extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready():
	
	print($HIVE.get_profile("bflanagin",true))
	$HIVE.get_img("profile","https://files.steempeak.com/file/steempeak/bflanagin/zPoz0tPK-profile.png","TextureRect",true)
	$HIVE.get_img("cover","https://files.steempeak.com/file/steempeak/bflanagin/RUeG6If9-DSC_0161.JPG","TextureRect2",true)
	#print($HIVE.get_profile("bflanagin",true))
	#$HIVE.get_history("bflanagin",-1,10,true)
	#$HIVE.get_blog_history("bflanagin",0,1)
	#$HIVE.call_deferred("get_blog_entry","bflanagin",336)
	#$HTTPRequest.request("https://files.steempeak.com/file/steempeak/bflanagin/zPoz0tPK-profile.png")
	
	pass # Replace with function body.
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	
	pass



func _on_hive_error(type, data):
	var box = $RichTextLabel
	box.append_text("from Error")
	box.append_text(str(type))
	box.append_text(" ")
	box.append_text(str(data)+"\n")
	


func _on_hive_received_profile(json):
	var box = $TabContainer/Profile/VBoxContainer/RichTextLabel
	box.append_text("\nFrom received profile\n")
	#box.append_text(str(json.keys()))
	#print(json)
	for key in json.keys():
		box.append_text("\n"+key+": ")
		if json[key] is String:
			box.append_text(json[key])
		if json[key] is Dictionary:
			#box.append_text("\n")
			for k in json[key].keys():
				box.append_text("\n     "+k+":")
				box.append_text(str(json[key][k]))
		if json[key] is float:
			box.append_text(str(json[key]))
	#if json["recieved"].has("result"):
	#	box.append_text(str(json["recieved"]["result"]))	
	


func _on_hive_received_history(json):
	var box =  $TabContainer/History/VBoxContainer/RichTextLabel
	box.append_text("\nFrom received history\n")
	#box.append_text(str(json))
	if json.has("history"):
		for p in json["history"]:
			box.append_text("\n"+str(p))


func _on_hive_received_blog_history(json):
	var box =  $TabContainer/Blog/VBoxContainer/RichTextLabel
	box.append_text("\nFrom received blog history\n")
	if json["received"].has("result"):
		for p in json["received"]["result"]:
			box.append_text("\n"+str(p))


func _on_hive_received_blog_entry(json):
	print("Blog entry")
	#var box =  $TabContainer/Blog/VBoxContainer/RichTextLabel
	#box.append_text("\nFrom recieved blog history\n")
	#box.append_text(str(json))
	print(str(json))



func _on_hive_received_img(data):
	var TR = ImageTexture.create_from_image(data["received"])
	for c in get_children():
		if c.name == data["obj"]:
			c.set_texture(TR)
			break



