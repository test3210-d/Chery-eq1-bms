Дослідження роботи бмс та фреймів які бігають в кан шині 

напруга іде від 1 комірки і далі, 10 c1 = 4289 mV все просто 

voltage frames

ID        DLC       Data                     

541      8   10 C1 10 B3 10 B6 10 B3 

542      8   10 B6 10 BE 10 B0 10 BE 

543      8   10 AF 10 AF 10 B8 10 BA 

544      8   10 C0 10 B8 10 BD 10 BF      

545      8   10 C3 10 C1 10 BD 10 B7     

546      8   10 BC 10 B9 10 BA 10 BC 

547      8   10 B2 10 B8 10 B6 10 B5 

548      8   10 BD 10 B9 10 B8 10 BC 

549      8   10 CB 10 C2 10 BE 10 C4 

54A      8   10 B6 10 BF 10 B6 10 BB 

54B      8   10 B6 10 BA 10 C2 10 C2 

54C      8   10 A6 10 BC 10 B7 10 BB 

54D      8   10 C1 10 B0 10 B3 10 B6 

54E      8   10 B9 10 BD 10 BE 10 B8 

54F      8   10 BD 10 BA 10 B9 10 BD 

550      8   10 BC 10 BE 10 B1 10 BD 

551      8   10 B9 10 BD 10 B8 10 BC 

552      8   10 B9 10 C5 10 BC 10 AD 

553      8   10 BF 10 B2 10 C1 10 B5 

554      8   10 B0 10 B5 10 B2 10 C3 

555      8   10 B7 10 BD 10 BA 10 BF 

556      8   10 B8 10 BC 10 B0 10 B1 

557      8   10 BE 10 B5 00 00 00 00  

Зроблено діагностичний скетч на esp32c3 mini, підключення через wi-fi, 
запчастини які потрібні , діод 1n4001 , плата esp32c3 mini, dc-dc 12-5v (або стабілізатор 5в) , obd 2 роз'єм

результат роботи

<table border="1"><tbody><tr><td>Мінімальна напруга .</td><td>4262</td></tr><tr><td>Максимальна напруга .</td><td>4300</td></tr></tbody></table><table border="1"><tbody><tr><td>Номер комірки .</td><td>Напруга на комірці .</td></tr><tr><td>1</td><td>4290</td></tr><tr><td>2</td><td>4275</td></tr><tr><td>3</td><td>4278</td></tr><tr><td>4</td><td>4276</td></tr><tr><td>5</td><td>4279</td></tr><tr><td>6</td><td>4286</td></tr><tr><td>7</td><td>4273</td></tr><tr><td>8</td><td>4286</td></tr><tr><td>9</td><td>4271</td></tr><tr><td>10</td><td>4272</td></tr><tr><td>11</td><td>4280</td></tr><tr><td>12</td><td>4283</td></tr><tr><td>13</td><td>4288</td></tr><tr><td>14</td><td>4280</td></tr><tr><td>15</td><td>4286</td></tr><tr><td>16</td><td>4288</td></tr><tr><td>17</td><td>4291</td></tr><tr><td>18</td><td>4289</td></tr><tr><td>19</td><td>4286</td></tr><tr><td>20</td><td>4280</td></tr><tr><td>21</td><td>4284</td></tr><tr><td>22</td><td>4281</td></tr><tr><td>23</td><td>4283</td></tr><tr><td>24</td><td>4285</td></tr><tr><td>25</td><td>4274</td></tr><tr><td>26</td><td>4279</td></tr><tr><td>27</td><td>4279</td></tr><tr><td>28</td><td>4278</td></tr><tr><td>29</td><td>4283</td></tr><tr><td>30</td><td>4281</td></tr><tr><td>31</td><td>4280</td></tr><tr><td>32</td><td>4284</td></tr><tr><td>33</td><td>4300</td></tr><tr><td>34</td><td>4291</td></tr><tr><td>35</td><td>4286</td></tr><tr><td>36</td><td>4293</td></tr><tr><td>37</td><td>4290</td></tr><tr><td>38</td><td>4275</td></tr><tr><td>39</td><td>4278</td></tr><tr><td>40</td><td>4276</td></tr><tr><td>41</td><td>4278</td></tr><tr><td>42</td><td>4287</td></tr><tr><td>43</td><td>4279</td></tr><tr><td>44</td><td>4284</td></tr><tr><td>45</td><td>4262</td></tr><tr><td>46</td><td>4284</td></tr><tr><td>47</td><td>4279</td></tr><tr><td>48</td><td>4283</td></tr><tr><td>49</td><td>4290</td></tr><tr><td>50</td><td>4272</td></tr><tr><td>51</td><td>4276</td></tr><tr><td>52</td><td>4278</td></tr><tr><td>53</td><td>4281</td></tr><tr><td>54</td><td>4286</td></tr><tr><td>55</td><td>4286</td></tr><tr><td>56</td><td>4280</td></tr><tr><td>57</td><td>4285</td></tr><tr><td>58</td><td>4282</td></tr><tr><td>59</td><td>4282</td></tr><tr><td>60</td><td>4286</td></tr><tr><td>61</td><td>4285</td></tr><tr><td>62</td><td>4287</td></tr><tr><td>63</td><td>4274</td></tr><tr><td>64</td><td>4285</td></tr><tr><td>65</td><td>4281</td></tr><tr><td>66</td><td>4286</td></tr><tr><td>67</td><td>4281</td></tr><tr><td>68</td><td>4284</td></tr><tr><td>69</td><td>4281</td></tr><tr><td>70</td><td>4293</td></tr><tr><td>71</td><td>4284</td></tr><tr><td>72</td><td>4269</td></tr><tr><td>73</td><td>4287</td></tr><tr><td>74</td><td>4274</td></tr><tr><td>75</td><td>4289</td></tr><tr><td>76</td><td>4277</td></tr><tr><td>77</td><td>4273</td></tr><tr><td>78</td><td>4278</td></tr><tr><td>79</td><td>4275</td></tr><tr><td>80</td><td>4292</td></tr><tr><td>81</td><td>4279</td></tr><tr><td>82</td><td>4286</td></tr><tr><td>83</td><td>4282</td></tr><tr><td>84</td><td>4287</td></tr><tr><td>85</td><td>4281</td></tr><tr><td>86</td><td>4284</td></tr><tr><td>87</td><td>4272</td></tr><tr><td>88</td><td>4273</td></tr><tr><td>89</td><td>4285</td></tr><tr><td>90</td><td>4284</td></tr> </tbody></table>
