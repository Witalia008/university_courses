Rails.application.routes.draw do
  resources :order_items
  resources :orders
  resources :admin_messages
  resources :messages
  resources :banners
  resources :news_items
  mount RailsAdmin::Engine => '/admin', as: 'rails_admin'
  get 'home/index'
  post 'home/backup'
  get 'home/thanks'
  get 'carts/edit'

  devise_for :users, controllers: { registrations: "users/registrations"}
  devise_scope :user do
    get "registrations/customer_signup", to: "users/registrations#new_customer", as: :new_customer
    get "registrations/worker_signup", to: "users/registrations#new_worker", as: :new_worker
    get "users/:id/image", to: "users/registrations#serve_image", as: :get_user_image
    get "users/:id", to: "users/registrations#show", as: :user
    post "registrations/create_customer", to: "users/registrations#create_customer", as: :create_customer
    post "registrations/create_worker", to: "users/registrations#create_worker", as: :create_worker
    get "users", to: "users/registrations#index", as: :users
    get "users/:id/services", to: "users/registrations#services", as: :user_services
    get "users/:id/new_message", to: "users/registrations#new_message", as: :user_new_message
    post "users/:id/create_message", to: "users/registrations#create_message", as: :user_create_message
  end

  resources :services do
    member do
      post "add_to_cart"
      delete "remove_from_cart"
      get "buy"
      post "order"
    end
  end
  resources :categories

  # The priority is based upon order of creation: first created -> highest priority.
  # See how all your routes lay out with "rake routes".

  # You can have the root of your site routed with "root"
  root 'home#index'

  # Example of regular route:
  #   get 'products/:id' => 'catalog#view'

  # Example of named route that can be invoked with purchase_url(id: product.id)
  #   get 'products/:id/purchase' => 'catalog#purchase', as: :purchase

  # Example resource route (maps HTTP verbs to controller actions automatically):
  #   resources :products

  # Example resource route with options:
  #   resources :products do
  #     member do
  #       get 'short'
  #       post 'toggle'
  #     end
  #
  #     collection do
  #       get 'sold'
  #     end
  #   end

  # Example resource route with sub-resources:
  #   resources :products do
  #     resources :comments, :sales
  #     resource :seller
  #   end

  # Example resource route with more complex sub-resources:
  #   resources :products do
  #     resources :comments
  #     resources :sales do
  #       get 'recent', on: :collection
  #     end
  #   end

  # Example resource route with concerns:
  #   concern :toggleable do
  #     post 'toggle'
  #   end
  #   resources :posts, concerns: :toggleable
  #   resources :photos, concerns: :toggleable

  # Example resource route within a namespace:
  #   namespace :admin do
  #     # Directs /admin/products/* to Admin::ProductsController
  #     # (app/controllers/admin/products_controller.rb)
  #     resources :products
  #   end
end
