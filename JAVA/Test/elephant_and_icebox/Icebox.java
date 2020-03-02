class Icebox{
	private int Size;
	private int door = 0;
	private int num = 0;
	private Elephant[] in;

	public Icebox(int Size){
		this.Size = Size;
		in = new Elephant[Size];
	}
	public void open(){
		if(door == 0){
			door = 1;
			System.out.println("冰箱门打开了");
		}
		else{
			System.out.println("冰箱门是开着的，请不要重复打开");
		}
	}
	public void close(){
		if(door == 1){
			door = 0;
			System.out.println("冰箱门关上了");
		}
		else{
			System.out.println("冰箱门是关着的，请不要重复关闭");
		}
	}
	public void push(Elephant anElephant){
		if(door == 1){
			if(num < Size){
				in[num++] = anElephant;
				System.out.println("装进一只大象"+anElephant);
			}
			else{
				System.out.println("冰箱已经满了,无法装进"+anElephant);
			}
		}
		else{
			System.out.println("冰箱门是关着的，无法放入");
		}
	}
	public void pop(){
		if(door == 1){
			if(num>0){
				System.out.println("拿出一只大象"+in[(num--)-1]);	
			}
			else{
				System.out.println("冰箱是空的，无法拿出");
			}
		}
		else{
			System.out.println("冰箱门是关着的，无法拿出");
		}
	}
}