print("Starting LGECore....");

App = CApp();
bkgrnd = "bg_tylerlivingroom.png";

init = false;
start = false;
complete = false;

function main()
	local res = -1;
	while not complete do
		if not start then
			print("Starting main application...");
			res = App.run();
		end
		if not init then
			print("Setting background to " .. bkgrnd);
			App.setBackground(bkgrnd);
		end
		complete = (res == 0);
	end
	co.yield();
end

main();